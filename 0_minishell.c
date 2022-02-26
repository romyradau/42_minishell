//testing out readline functon

#include "minishell.h"

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


int	empty_input(char *input)
{
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			return (1);
		}
		return (0);
}

int	prompt(t_data *data)
{
	char	*input;
	char	*user;
	struct	sigaction sa;

	sa.sa_handler = btn_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	//TODO eigene function

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	while (1)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (-1);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (-1);
		//TODO eigene function
		input = readline(user);
		if (empty_input(input))
			return (1);

		/* start parsing */
		data->processes = special_split(input, '|');
		//freen?
		if (!data->processes)
		{
			printf("error: unclosed quotes");
			return 1;
			//wie sieht error handling bei open quotes aus?
			//soll da gleich in die neue prompt gegangen werden?
			//nicht nur returnen sondern einfach mit nachster prompt weiter machen
			//TODO eigene function
		}
		data->processes = trim_spaces(data);
		//protecten??
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
	ft_bzero(&data, sizeof(t_data));
	data.env = env;
	if (prompt(&data))
	{
		//free
		//correct error message
		return(1);
	}
	return (0);
}

/*
main = introduction of t_data & stores env & sends to->
prompt = readline & packages vorbereiten
process_packages = pusht die packages & setzt den pipe bool fur alle packages
*/