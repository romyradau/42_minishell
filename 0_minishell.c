
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
		free(data->processes[i]);
		data->processes[i] = ft_strtrim(temp, " ");
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
			if (!process_packages(data, builtin))
			{
				unset_attr();
				execute_packages(input, data, builtin);
			}
			kill_d_str(data->processes);
			free_packages(data);
		}
	}
	return (0);
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
	// input = argv[1];
	(void)argv;
	g_exit_stat = 0;
	ft_bzero(&data, sizeof(t_data));
	data.env = envp;
	builtin->home_path = getenv("HOME");
	set_envlist(&data, &builtin->env_list);
	if (handle_input(&data, builtin))
		return (1);
	return (0);
}

/*
main = introduction of t_data & stores env & sends to->
prompt = readline & packages vorbereiten
process_packages = pusht die packages & setzt den pipe bool fur alle packages
*/