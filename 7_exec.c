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
//muss ich noch infile und outfile initialisieren?
	return (ret);
}


void	open_heredoc(char *limiter, t_file *file)
{
	char	*line;
	char	*test;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			perror("readline");
		test = ft_strtrim(line, "\n");
		if (!ft_strncmp(test, limiter, ft_strlen(limiter) + 1))
		//warum hier die plus 1?? fur die nullterminante??
		{
			free(test);
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(test);
		free(line);
	}
	fprintf(stderr, "infile	%d\n", file->infile);
	fprintf(stderr, "fd[0]	%d\n", fd[0]);

	file->infile = fd[0];
	fprintf(stderr, "infile after dup	%d\n", file->infile);

	//muss man dupen oder geht's auch ohne ?
	// close(fd[0]);
	close(fd[1]);
}

void	redirect_infiles(t_package *package, t_file *file)
{
	int	i;

	i = 0;

	printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
	while(package->in_redirection[i])
	{

		if (package->in_redirection[i] == INFILE)
		{

			file->infile = open(package->infiles[i], O_RDONLY);
			if (file->infile == -1)
				perror("open fail");
		}
		else if (package->in_redirection[i] == HEREDOC)
			open_heredoc(package->infiles[i], file);
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

	if (current->in_redirection[0] != NOTHING)
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

int	find_path(char **paths, t_package *current, char **envp)
{
	int		i;
	char	*match;
	char	*tmp_match;
	struct stat s;

	if (ft_strchr(current->cmd, '/') || paths == NULL)
	{
		execve(current->cmd, current->cmd_args, envp);
		printf("minishell: %s: %s\n", current->cmd_args[0], strerror(errno)); //stderr
		if (errno == ENOENT)
			return (127);
		else
			return (126);
	}
	//hier hab ich keine Auswahlmoglichkeiten, deswegen soll direkt nach execve gechect werden
	//kein access weil sonst der error abgefangen wird?!
	else
	{
		i = 0;
		while (paths && paths[i])
		{
			tmp_match = ft_strjoin(paths[i], "/");
			match = ft_strjoin(tmp_match, current->cmd);
			free(tmp_match);
			//vlt noch access hier
			if (access(match, F_OK) == 0 && (!stat(match, &s) && !S_ISDIR(s.st_mode))) // directory checken )
			{
				execve(match, current->cmd_args, envp);
				printf("minishell: %s: %s\n", current->cmd_args[0], strerror(errno)); //stderr
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
	//theoretisch auch nocha lels andere freen
	//eien free function
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
	int status;
	(void)envp;
	t_file	*file;

	file = init_redirections();

	// printf("hali\n");
	while (data->head)
	{
		if (pipe(file->fd) == -1) // data->head->next
			perror("pipe");
		file->pid = fork();
		if (file->pid == -1)
			perror("fork");
		if (file->pid == 0)
		{
			close(file->fd[0]);
			links(file, data->head); // war file oeffnen erfolgreich sonst exiten
			rechts(file, data->head); // wenns schief lauft exiten mit passenden fehler codes
			close(file->in); 
			do_the_execution(data->head, data->env);
		}
		close(file->fd[1]);
		redirect_parent(file, data->head);
		data->head = data->head->next;
	}
	close(file->tmp_fd);
	close(file->in);
	close(file->out);
	waitpid(file->pid, &status, 0); // exitstatus
	//fur file->pid fragt er den exit status ab
	while (wait(NULL) > 0);
	if (WIFSIGNALED(status))
	{
		printf("%d\n", WTERMSIG(status) + 128);
		g_exit_stat = WTERMSIG(status) + 128;
	}
	else
	{
		printf("%d\n", WEXITSTATUS(status));
		g_exit_stat = WEXITSTATUS(status);
	}
	free(file);
}
//ausser bei nur einem builtin, dann alles im parent!