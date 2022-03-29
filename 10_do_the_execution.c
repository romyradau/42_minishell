/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_do_the_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:05:39 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 20:05:48 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_protection(int *fd, int aim)
{
	g_exit_stat = (
			dup2((*fd), aim) == -1
			|| close ((*fd)) == -1
			);
	if (g_exit_stat == 1)
		perror("minishell");
}

void	redirect_parent(t_file *file)
{
	g_exit_stat = (
			dup2(file->fd[0], file->tmp_fd) == -1
			|| close(file->fd[0]) == -1
			);
	if (g_exit_stat == 1)
		perror("minishell");
}

int	join_path(char **paths, t_package *current, int i, char **envp)
{
	char		*match;
	char		*tmp_match;
	struct stat	s;

	tmp_match = ft_strjoin(paths[i], "/");
	match = ft_strjoin(tmp_match, current->cmd);
	if (!tmp_match || !match)
		return (1);
	free(tmp_match);
	if (access(match, F_OK) == 0
		&& (!stat(match, &s) && !S_ISDIR(s.st_mode)))
	{
		execve(match, current->cmd_args, envp);
		perror("minishell");
		return (126);
	}
	free(match);
	return (0);
}

int	find_path(char **paths, t_package *current, char **envp)
{
	int	i;

	if (ft_strchr(current->cmd, '/') || paths == NULL)
	{
		execve(current->cmd, current->cmd_args, envp);
		perror(current->cmd_args[0]);
		if (errno == ENOENT)
			return (127);
		else
			return (126);
	}
	else
	{
		i = 0;
		while (paths && paths[i])
		{
			if (join_path(paths, current, i, envp) == 1)
				return (1);
			else if (join_path(paths, current, i, envp) == 126)
				return (126);
			i++;
		}
		printf("minishell: %s: command not found\n", current->cmd_args[0]);
		return (127);
	}
}

void	do_the_execution(t_package *current, char **envp, t_data *data)
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
	kill_d_str(paths);
	free_packages(data);
	exit(error);
}
