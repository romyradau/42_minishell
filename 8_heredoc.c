
#include "minishell.h"

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
