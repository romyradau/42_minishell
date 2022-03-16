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
	int	temp;

	i = 0;

	printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
	while(package->in_redirection[i])
	{
		if (package->in_redirection[i] == 3)
		{
			temp = open(package->infiles[i], O_RDONLY);
			if (temp == -1)
				perror("open fail");
		}
		if (package->in_redirection[i] == 5)
		{
			open_heredoc(package->infiles[i]);
		}
		printf("in_redirection:		%d\n", package->in_redirection[i]);
		i++;

	}
	file->tmp_fd = dup(temp);
	printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void	execute_function(t_data *data)
{
	t_file	*file;

	file = init_redirections();

	printf("hali\n");
	while (data->head)
	{
		redirect_infiles(data->head, file);
		data->head = data->head->next;
	}

	free(file);

}