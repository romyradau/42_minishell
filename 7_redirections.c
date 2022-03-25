#include "minishell.h"

t_file	*init_redirections(void)
{
	t_file	*ret;

	ret = malloc(sizeof(t_file));
	if (ret == NULL)
		return (NULL);
	ret->in = dup(STDIN_FILENO);
	ret->out = dup(STDOUT_FILENO);
	ret->tmp_fd = dup(STDIN_FILENO);
	ret->infile = -1;
	ret->outfile = -1;
	ret->heredoc = -1;
	ret->limiter = NULL;
	ret->fd[0] = -1;
	ret->fd[1] = -1;
	ret->pid = -1;
	return (ret);
}

int	handle_heredoc(char *line, char *limiter)
{
	char	*test;

	if (line == NULL)
	{
		free(line);
		return (1);
	}
	test = ft_strtrim(line, "\n");
	if (test == NULL)
	{
		free(line);
		return (1);
	}
	if (!ft_strncmp(test, limiter, ft_strlen(limiter) + 1))
	{
		free(test);
		free(line);
		return (1);
	}
	free (test);
	return (0);
}

void	open_heredoc(char *limiter, t_file *file)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe: ");
	while (1)
	{
		signal(SIGINT, sig_in_heredoc);
		line = readline("> ");
		if (handle_heredoc(line, limiter))
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	file->infile = fd[0];
	if (close(fd[1]) == -1)
		perror("pipe: ");
}

int	redirect_infiles(t_package *package, t_file *file)
{
	int	i;

	i = 0;
	while (package->in_redirection[i])
	{
		if (package->in_redirection[i] == INFILE)
		{
			file->infile = open(package->infiles[i], O_RDONLY);
			if (file->infile == -1)
			{
				fprintf(stderr,"minshell: %s: No such file or directory\n", package->infiles[i]);
				g_exit_stat = 1;
				return (g_exit_stat = 1);
			}
		}
		else if (package->in_redirection[i] == HEREDOC)
			open_heredoc(package->infiles[i], file);
		if (package->in_redirection[i + 1])
			if (close(file->infile) == -1)
				g_exit_stat = 1;
		i++;
	}
	g_exit_stat = (
			dup2(file->infile, file->tmp_fd) == -1
			|| close(file->infile) == -1
			);
	return (g_exit_stat);
}

int	links(t_file *file, t_package *current)
{
	if (current->in_redirection[0] != NOTHING)
	{
		if (redirect_infiles(current, file) == 1)
			return (1);
	}
	g_exit_stat = (
			dup2(file->tmp_fd, STDIN_FILENO) == -1
			|| close(file->tmp_fd) == -1
			);
	return (g_exit_stat);
}

int	rechts(t_file *file, t_package *current)
{
	int	i;

	if (current->pipe && current->out_redirection[0] == NOTHING)
	{
		g_exit_stat = (
				dup2(file->fd[1], STDOUT_FILENO) == -1
				);
	}
	else if (current->out_redirection[0] != NOTHING)
	{
		i = 0;
		while (current->out_redirection[i])
		{
			if (current->out_redirection[i] == TRUNCATE)
				file->outfile = open(current->outfiles[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (current->out_redirection[i] == APPEND)
				file->outfile = open(current->outfiles[i], O_RDWR | O_CREAT | O_APPEND, 0644);
			if (file->outfile == -1)
			{
				perror(current->outfiles[i]);
				g_exit_stat = 1;
			}
			if (current->out_redirection[i + 1])
				if (close(file->outfile) == -1)
					g_exit_stat = 1;
			i++;
			// evtl muss bei error infiles geclosed werden
		}
		g_exit_stat = (
				dup2(file->outfile, STDOUT_FILENO) == -1
				|| close (file->outfile) == -1
				);
	}
	else
	{
		g_exit_stat = (
				dup2(file->out, STDOUT_FILENO) == -1
				|| close (file->out) == -1
				);
	}
	return (g_exit_stat);
}

int	find_path(char **paths, t_package *current, char **envp)
{
	int		i;
	char	*match;
	char	*tmp_match;
	struct stat s;

	if (ft_strchr(current->cmd, '/') || paths == NULL)
	//für welchen case ist das nochmal genau? wgen / im input
	{
		execve(current->cmd, current->cmd_args, envp);
		printf("minishell: %s: %s\n", current->cmd_args[0], strerror(errno)); //stderr
		if (errno == ENOENT)
			return (127);
			//error no entry
		else
			return (126);
	}
	else
	{
		i = 0;
		while (paths && paths[i])
		{
			tmp_match = ft_strjoin(paths[i], "/");
			match = ft_strjoin(tmp_match, current->cmd);
			if (!tmp_match || !match)
				return (1);
			free(tmp_match);
			//vlt noch access hier
			if (access(match, F_OK) == 0 && (!stat(match, &s) && !S_ISDIR(s.st_mode))) // directory checken )
			{
				execve(match, current->cmd_args, envp);
				printf("minishell: %s: %s\n", current->cmd_args[0], strerror(errno)); //TODO:error funtion
				return (126);
			}
			free(match);
			i++;
		}
		printf("minishell: %s: command not found\n", current->cmd_args[0]); //stderr
		return (127);
	}
}

void	do_the_execution(t_package *current, char **envp)
{
	char	**paths;
	int		i;
	int		error;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 6, ':');
	error = find_path(paths, current, envp);
	free(paths);
	exit(error);
}
	/*
	theoretisch auch noch alles andere freen
	eine free function
	wenn das heir hin kommt, dann ist was schief gelaufen 
	*/

int	redirect_parent(t_file *file)
{
	int	error;

	error = (
			dup2(file->fd[0], file->tmp_fd) == -1
			|| close(file->fd[0]) == -1
			);
	return (error);
}
//was wenn das schief schlagt?