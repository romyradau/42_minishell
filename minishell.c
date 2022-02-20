//testing out readline functon

#include "minishell.h"


int process_tokens(t_data *data)
{
	char	*current_process;
	int		i;


	i = 0;
	current_process = data->processes[i];
	while (data->processes[i])
	{
		push_package(&data->head, data->processes[i]);
		// check_metachars(data->head, current_process);
		//wie kann ich mir fur meine struct die pipes abseichern?
		i++;
	}
	// check_quotes();


	// if (push_package(package, simple_cmd))
	// 	return (1);
	return (0);
}

char	**trim_spaces(t_data *data)
{
	char	*temp;

	int i = 0;
	while (data->processes[i])
	{
		temp = data->processes[i];
		free(data->processes[i]);
		data->processes[i] = ft_strtrim(temp, " ");
		i++;
	}
	return (data->processes);
}

int	prompt(t_data *data)
{
	char	*input;
	char	*user;
	struct sigaction sa;

	sa.sa_handler = btn_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	while (1)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (-1);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (-1);
		input = readline(user);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			return (1);
		}
		/* start parsing */
		data->processes = special_split(input, '|');
		if (!data->processes)
		{
			printf("error");
			return 1;
			//nicht nur returnen sondern einfach mit nachster prompt weiter machen
		}
		data->processes = trim_spaces(data);
		print2Darray(data->processes);
		// (void)split;
		process_tokens(data);

		// if (push_package(package, input))
		// 	return (1);
		/* end parsing */

		/* start execution */

		/* end execution */
		print_package(data->head);
		add_history(input);
	}
	return (0);
}

int	main(int argc, char **argv, char	**env)
{
	t_data		data;
	// char		*wc_args[5];

	(void) argc;
	(void) argv;

	//TODO: wired spaces maybe problem
	// wc_args[0] = "wc";
	// wc_args[1] = "-l";
	// wc_args[2] = " ";
	// wc_args[3] = " ";
	// wc_args[4] = " ";


	// execve("/usr/bin/wc", wc_args, env);
	data.env = env;
	//env in data.env speichern
	data.head = NULL;
	
	// char	*cmds[3];
	// cmds[0] = "ls";
	// cmds[1] = "-l";
	// cmds[2] = NULL;

	// execve("/bin/ls", cmds, env);

	if (prompt(&data))
	{
		//free
		//correct error message
		return(1);
	}
	return (0);
}
