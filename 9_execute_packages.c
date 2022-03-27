#include "minishell.h"

void	execute_cp(t_file *file, t_data *data, t_builtin *builtin)
{
	// signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	close(file->fd[0]);//TODO:protect
	if (links(file, data->head) == 1)
		exit(1);
	if (rechts(file, data->head) == 1)
		exit(1);
	close (file->fd[1]);//TODO:protect
	// close(file->infile);//TODO:protect
	if (check_if_builtin(data->head))
	{
		builtin_picker(data->head, builtin);
		exit(0);
	}
	else
		do_the_execution(data->head, data->env, data);
}

void	execute_function(t_data *data, t_builtin *builtin, t_file *file)
{
	int	status;

	while (data->head)
	{
		if (pipe(file->fd) == -1)
			perror("pipe");
		file->pid = fork();
		if (file->pid == -1)
			perror("fork");
		if (file->pid == 0)
			execute_cp(file, data, builtin);
		close(file->fd[1]);//TODO:protect
		redirect_parent(file);//TODO:was wenn das schief schlagt!!!???
		data->head = data->head->next;
	}
	close(file->tmp_fd);//TODO:protect
	close(file->in);//TODO:protect
	close(file->out);//TODO:protect
	waitpid(file->pid, &status, 0);
	while (wait(NULL) > 0);
	if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(status) + 128;
	else
		g_exit_stat = WEXITSTATUS(status);
}

int	execute_single_builtin(t_file *file, t_data *data, t_builtin *builtin)
{
	int	error;

	links(file, data->head);
	if (rechts(file, data->head) == 1)
	{
		g_exit_stat = 1;
		return (1);
	}	
	builtin_picker(data->head, builtin);
	error = (
			dup2(file->out, STDOUT_FILENO) == -1
			|| dup2(file->in, STDIN_FILENO) == -1
			|| close(file->tmp_fd) == -1
			|| close(file->in) == -1
			|| close(file->out) == -1
			);
	return (error);
}

void	execute_packages(char *in, t_data *data, t_builtin *bi)
{
	// t_file	*file;

    init_redirections(&data->file);
	add_history(in);
	if (check_if_builtin(data->head) && data->head->next == NULL)
		execute_single_builtin(&data->file, data, bi);
	else
		execute_function(data, bi, &data->file);
}

/*TODO: was soll denn genau passieren wenn hier etwas schief lauft?
wie soll man die ganzen 
dup
close
pipe 
errors handlen??
*/
