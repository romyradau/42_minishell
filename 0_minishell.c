
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

char	**trim_spaces(t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->processes[i])
	{
		temp = data->processes[i];
		data->processes[i] = ft_strtrim(temp, " ");
		free(temp);
		i++;
	}
	return (data->processes);
}

int	prepare_packages(t_data *data, char *input)
{
	data->processes = special_pipe_split(input, '|');
	if (!data->processes)
		return (1);
	data->processes = trim_spaces(data);
	return (0);
}

int	handle_input(t_data *data, t_builtin *builtin)
{
	char	*user;
	char	*input;

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		set_attr();
		input = readline(user);
		errno = 0;
		if (empty_input(input))
		{
			if (prepare_packages(data, input))
				return (1);
			if (data->processes[0][0] != 0 && !process_packages(data, builtin))
			{
				unset_attr(data->head);
				execute_packages(input, data, builtin);
			}
			kill_d_str(data->processes);
			free_packages(data);
		}
		free(input);
	}
	return (0);
}

void	free_env(t_builtin *builtin)
{
	t_envlist *tmp;

	while(builtin->env_list != NULL)
	{
		free(builtin->env_list->content);
		tmp = builtin->env_list;
		builtin->env_list = builtin->env_list->next;
		free(tmp);
	}
	free(builtin);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_builtin	*builtin;

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
	handle_input(&data, builtin);
	// free_env(builtin);
	return (0);
}
