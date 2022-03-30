/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_execute_packages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:59:53 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/30 14:23:20 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (check_if_builtin(data->head))
	{
		builtin_picker(data->head, bi, env_cpy);
		exit(0);
	}
	else
		do_the_execution(data->head, (*env_cpy), data);
}

void	get_error_code(t_file *file)
{
	int	status;

	close(file->tmp_fd);
	close(file->in);
	close(file->out);
	waitpid(file->pid, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFSIGNALED(status))
		g_exit_stat = WTERMSIG(status) + 128;
	else
		g_exit_stat = WEXITSTATUS(status);
}

void	execute(t_data *data, t_builtin *bi, t_file *file, char ***env_cpy)
{
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
	get_error_code(file);
}

void	single(t_file *file, t_data *data, t_builtin *builtin, char ***env_cpy)
{
	int	error;

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
