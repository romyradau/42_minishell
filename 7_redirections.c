#include "minishell.h"

void	init_redirections(t_file *ret)
{
	ret->in = dup(STDIN_FILENO);
	ret->out = dup(STDOUT_FILENO);
	ret->tmp_fd = dup(STDIN_FILENO);
	ret->infile = -1;
	ret->of = -1;
	ret->heredoc = -1;
	ret->limiter = NULL;
	ret->fd[0] = -1;
	ret->fd[1] = -1;
	ret->pid = -1;

}

int	redirect_infiles(t_package *package, t_file *file)
{
	int	i;

	i = 0;
	set_termios();
	while (package->in_redirection[i])
	{
		if (package->in_redirection[i] == INFILE)
		{
			file->infile = open(package->infiles[i], O_RDONLY);
			if (file->infile == -1)
			{
				perror(package->infiles[i]);
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
	dup2_protection(&file->infile, file->tmp_fd);
	return (g_exit_stat);
}

int	links(t_file *file, t_package *current)
{
	if (current->in_redirection[0] != NOTHING)
	{
		if (redirect_infiles(current, file) == 1)
			return (1);
	}
	dup2_protection(&file->tmp_fd, STDIN_FILENO);
	return (g_exit_stat);
}

int	redirect_outfiles(t_package *curr, int i, t_file *file)
{
	if (curr->out_redirection[i] == TRUNCATE)
		file->of = open(curr->outfiles[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (curr->out_redirection[i] == APPEND)
		file->of = open(curr->outfiles[i], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file->of == -1)
	{
		perror(curr->outfiles[i]);
		if (file->infile > -1)
			close(file->infile);
		g_exit_stat = 1;
		return (1);
	}
	if (curr->out_redirection[i + 1])
		if (close(file->of) == -1)
			g_exit_stat = 1;
	return (0);
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
			if (redirect_outfiles(current, i, file))
				return (1);
			i++;
		}
		dup2_protection(&file->of, STDOUT_FILENO);
	}
	else
		dup2_protection(&file->out, STDOUT_FILENO);
	return (g_exit_stat);
}
