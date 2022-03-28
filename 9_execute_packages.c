#include "minishell.h"

void	execute_cp(t_file *file, t_data *data, t_builtin *bi, char ***env_cpy)
{
	signal(SIGINT, SIG_DFL);
	close(file->fd[0]);
	if (links(file, data->head) == 1)
		exit(1);
	if (rechts(file, data->head) == 1)
		exit(1);
	close (file->fd[1]);
	// close(file->infile)?? brauchts das vlt noch?
	if (check_if_builtin(data->head))
	{
		builtin_picker(data->head, bi, env_cpy);
		exit(0);
	}
	else
		do_the_execution(data->head, (*env_cpy), data);
}

void	execute(t_data *data, t_builtin *bi, t_file *file, char ***env_cpy)
{
	int	status;

	while (data->head)
	{
		if (pipe(file->fd) == -1)
		{
			perror("pipe");
			break ;
		}
		file->pid = fork();
		if (file->pid == -1)
		{
			perror("fork");
			break ;
		}
		if (file->pid == 0)
			execute_cp(file, data, bi, env_cpy);
		close(file->fd[1]);
		redirect_parent(file);
		data->head = data->head->next;
	}
	close(file->tmp_fd);//TODO:protect
	close(file->in);//TODO:protect
	close(file->out);//TODO:protect
	waitpid(file->pid, &status, 0);//auf den zuletzt ausgefuhrten prozess
	while (wait(NULL) > 0);// uaf irgenein child
	if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(status) + 128;
	else
		g_exit_stat = WEXITSTATUS(status);
}

void	single(t_file *file, t_data *data, t_builtin *builtin, char ***env_cpy)
{
	int error;

	close(file->in);
	close(file->tmp_fd);
	if (rechts(file, data->head) == 1)
	{
		g_exit_stat = 1;
		return ;
	}
	builtin_picker(data->head, builtin, env_cpy);
	if (data->head->out_redirection[0] != NOTHING)
	{
		error = (
				dup2(file->out, STDOUT_FILENO) == -1
				|| close(file->out) == -1
				);
		if (error == 1)
			perror("minishell");
	}
}

void	exec_packages(char *in, t_data *data, t_builtin *bi, char ***env_cpy)
{

	init_redirections(&data->file);
	add_history(in);
	if (check_if_builtin(data->head) && data->head->next == NULL)
		single(&data->file, data, bi, env_cpy);
	else
		execute(data, bi, &data->file, env_cpy);
}
