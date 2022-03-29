/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:15:57 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 20:09:42 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_input(char *input)
{
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	else if (input[0] == 0)
		return (0);
	return (1);
}

int	prepare_packages(t_data *data, char *input)
{
	data->processes = special_pipe_split(input, '|');
	if (!data->processes)
		return (1);
	data->processes = trim_spaces(data);
	return (0);
}

void	do_shell(t_data *data, t_builtin *builtin, char *input, char ***envcp)
{
	if (data->processes[0][0] != 0 && !parsepackages(data, builtin))
	{
		unset_attr(data->head);
		exec_packages(input, data, builtin, envcp);
	}
	free_packages(data);
}

int	handle_input(t_data *data, t_builtin *builtin, char ***env_cpy)
{
	char	*input;
	char	*user;

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		set_attr();
		input = readline(user);
		errno = 0;
		if (empty_input(input))
		{
			if (!input)
				return (1);
			if (!prepare_packages(data, input))
			{
				do_shell(data, builtin, input, env_cpy);
			}
			else
				add_history(input);
			kill_d_str(data->processes);
		}
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_builtin	*builtin;
	char		**cpy_env;

	builtin = (t_builtin *)malloc(sizeof(t_builtin));
	if (!builtin)
		return (0);
	builtin->env_list = NULL;
	(void) argc;
	(void)argv;
	g_exit_stat = 0;
	ft_bzero(&data, sizeof(t_data));
	data.env = envp;
	builtin->home_path = getenv("HOME");
	set_envlist(&data, &builtin->env_list);
	cpy_env = ft_calloc(env_list_len(builtin->env_list) + 2, sizeof(char *));
	if (!cpy_env)
		return (0);
	set_new_env(&cpy_env, builtin->env_list);
	handle_input(&data, builtin, &cpy_env);
	free_env(builtin);
	kill_d_str(cpy_env);
	return (0);
}
