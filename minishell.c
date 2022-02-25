//testing out readline functon

#include "minishell.h"

int process_packages(t_data *data)
{
	t_package	*current_package;
	int		i;

	i = 0;
	while (data->processes[i])
	{
		if (data->processes[i][0] != '\0')
			push_package(&data->head, data->processes[i]);
		//braucht man != '\0' noch??? nicht wirklich but i keep it though - glaube das war weil's eins zu viel gab mit ner \0 drin
		current_package = data->head;
		if (data->processes[i] != NULL)
		{
			while (current_package->next)
			{
				current_package->pipe = true;
				current_package = current_package->next;
			}
		}
		i++;
	}
	return (0);
}
//pusht die packages
//setzt den pipe bool fur alle packages

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
//trimt von den pipe_packages noch überflussige spaces ab
//damit im weiteren Verlauf wirklich nur mit dem string gearbeitet werden kann

int	prompt(t_data *data)
{
	char	*input;
	char	*user;
	struct	sigaction sa;

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
		//TODO eigene function
		input = readline(user);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			return (1);
		}
		//TODO eigene function

		/* start parsing */
		data->processes = special_split(input, '|');
		//freen?
		if (!data->processes)
		{
			printf("error");
			return 1;
			//nicht nur returnen sondern einfach mit nachster prompt weiter machen
		}
		data->processes = trim_spaces(data);
		print2Darray(data->processes);
		process_packages(data);

		/* end parsing */

		/* start execution */
		/* end execution */

		print_package(data->head);
		add_history(input);
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char	**env)
{
	t_data		data;

	(void) argc;
	(void) argv;
	data.env = env;
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
