#include "minishell.h"

void	execute_function(t_data *data, char **envp, t_builtin *builtin, t_file *file)
{
	int status;
	(void)envp;
	while (data->head)
	{
		if (pipe(file->fd) == -1)
			perror("pipe");
		file->pid = fork();
		if (file->pid == -1)
			perror("fork");
		if (file->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			close(file->fd[0]);//TODO:protect
			if (links(file, data->head) == 1)
				exit(1);// war file oeffnen erfolgreich sonst exiten
			if (rechts(file, data->head) == 1) // wenns schief lauft exiten mit passenden fehler codes
			//TODO:wann perror
			//wann exit
			//wann printf??
				exit(1);
			close (file->fd[1]);//TODO:protect
			close(file->in);//TODO:protect
			if (check_if_builtin(data->head))
			{
				builtin_picker(data->head, builtin);
				exit(0);
			}
			else
				do_the_execution(data->head, data->env);
		}
		close(file->fd[1]);//TODO:protect
		redirect_parent(file, data->head);
			//TODO:was wenn das schief schlagt!!!???
		data->head = data->head->next;
	}
	close(file->tmp_fd);//TODO:protect
	close(file->in);//TODO:protect
	close(file->out);//TODO:protect
	waitpid(file->pid, &status, 0);//wartet auf alle
	while (wait(NULL) > 0);//wartet auf jeden einzelnen
	if (WIFSIGNALED(status))
	{
		// printf("WIFSIGNALED %d\n", WTERMSIG(status) + 128);
		g_exit_stat = WTERMSIG(status) + 128;
	}
	else
	{
		// printf("WEXITSTATUS %d\n", WEXITSTATUS(status));
		g_exit_stat = WEXITSTATUS(status);
	}
	free(file);
}

int	execute_single_builtin(t_file *file, t_data *data, t_builtin *builtin)
{
	int	error;

	rechts(file, data->head);
	links(file, data->head);
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
//TODO: was soll denn genau passieren wenn hier etwas schief lauft?
/*wie soll man die ganzen 
dup
close
pipe 
errors handlen??
*/

void	execute_packages(char *input, t_data * data, t_builtin *builtin, char **envp)
{
	t_file	*file;

	file = init_redirections();
	add_history(input);
	if (check_if_builtin(data->head) && data->head->next == NULL)
		execute_single_builtin(file, data, builtin);
	else
		execute_function(data, envp, builtin, file);
}
