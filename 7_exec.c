#include "minishell.h"

t_file *init_redirections()
{
	t_file	*ret;

	ret = malloc(sizeof(t_file));
	if (ret == NULL)
		return NULL;
	ret->in = dup(STDIN_FILENO);
	ret->out = dup(STDOUT_FILENO);
	ret->tmp_fd = dup(STDIN_FILENO);
	ret->heredoc = -1;
	ret->limiter = NULL;
	ret->fd[0] = -1;
	ret->fd[1] = -1;
	ret->pid = -1;

	return (ret);
}


void	open_heredoc(char *limiter)
{
	char	*line;
	char	*test;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe fail");
	}

	while (1)
	{
		line = readline("> ");
		if (!line)
			perror("ERROR: missing here_doc input");
		test = ft_strtrim(line, "\n");
		if (!ft_strncmp(test, limiter, ft_strlen(limiter) + 1))
		{
			free(test);
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(test);
		free(line);
	}
}

void	redirect_infiles(t_package *package, t_file *file)
{
	int	i;
	// int	/temp;

	i = 0;

	printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
	while(package->in_redirection[i])
	{
		if (package->in_redirection[i] == 3)
		{
			file->infile = open(package->infiles[i], O_RDONLY);
			if (file->infile == -1)
				perror("open fail");
		}
		// if (package->in_redirection[i] == 5)
		// {
		// 	open_heredoc(package->infiles[i]);
		// }
		printf("in_redirection:		%d\n", package->in_redirection[i]);
		if (package->in_redirection[i + 1])
			close(file->infile);
		i++;
	}
	dup2(file->infile, file->tmp_fd);
	close(file->infile);
	printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int		links(t_file *file, t_package *current)
{
	int error;

	if (current->in_redirection[0])
	{
		redirect_infiles(current, file);
	}
	error = (
			dup2(file->tmp_fd, STDIN_FILENO) == -1
			|| close(file->tmp_fd) == -1
	);
	return (error);
}


int		rechts(t_file *file, t_package *current)
{
	int	error;
	int	i;

	if (current->pipe && current->out_redirection[0] == NOTHING)
	{
		error = (
			dup2(file->fd[1], STDOUT_FILENO) == -1
			// || close (file->fd[1]) == -1
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
			if (current->out_redirection[i + 1])
				close(file->outfile);
			i++;
			// evtl muss bei error infiles geclosed werden
			// evtl bei outfiles und pipe nochmal gucken ob die redirections passen
		}
		error = (
				dup2(file->outfile, STDOUT_FILENO) == -1
				|| close (file->outfile) == -1
		);

	}
	else
	{
		error = (
			dup2(file->out, STDOUT_FILENO) == -1
			|| close (file->out) == -1
		);
	}
	close (file->fd[1]);
	return (error);
}

void	find_path(char **paths, t_package *current, char **envp)
{
	int		i;
	char	*match;
	char	*tmp_match;

	i = 0;
	while (paths && paths[i])
	{
		tmp_match = ft_strjoin(paths[i], "/");
		match = ft_strjoin(tmp_match, current->cmd);
		free(tmp_match);
		//vlt noch access hier
		if (access(match, F_OK) == 0)
			execve(match, current->cmd_args, envp);
		free(match);
		i++;
	}
	//kein access weil sonst der error abgefangen wird?!
		// execve(current->cmd, current->cmd_args, envp);
}

void	do_the_execution(t_package *current, char **envp)
{

	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 6, ':');
	find_path(paths, current, envp);
	free(paths);
	//wenn das heir hin kommt, dann ist was schief gelaufen
}

int	redirect_parent(t_file *file, t_package *current)
{
	(void)current;
	int error;

	error = (
			dup2(file->fd[0], file->tmp_fd) == -1
			|| close(file->fd[0]) == -1
	);
	return (error);
}


void	execute_function(t_data *data, char **envp)
{
	(void)envp;
	t_file	*file;

	file = init_redirections();

	// printf("hali\n");
	while (data->head)
	{
		if (pipe(file->fd) == -1)
			perror("pipe");
		file->pid = fork();
		if (file->pid == -1)
			perror("fork");
		if (file->pid == 0)
		{
			close(file->fd[0]);
			links(file, data->head);
			rechts(file, data->head);
			do_the_execution(data->head, data->env);
		}
		waitpid(file->pid, NULL, 0);
		close(file->fd[1]);
		redirect_parent(file, data->head);
		data->head = data->head->next;
	}
	close(file->tmp_fd);
	free(file);
}
//ausser bei nur einem builtin, dann alles im parent!