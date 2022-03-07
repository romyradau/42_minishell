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

int	prompt(t_data *data, t_builtin *builtin)
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
		data->processes = special_pipe_split(input, '|');
		//freen?
		if (!data->processes)
		{
			printf("error: unclosed quotes\n");
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
		print_package(data->head, builtin);
		add_history(input);
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_builtin *builtin;
	builtin = (t_builtin *)malloc(sizeof(t_builtin));
	if (!builtin)
		return (0);	
	builtin->env_list = NULL;//(t_envlist *)malloc(sizeof(t_envlist));
	// if (!builtin->env_list)
	// 	return (0);
	(void) argc;
	(void) argv;
	ft_bzero(&data, sizeof(t_data));
	// ft_bzero(&builtin->env_list, sizeof(t_envlist));
	data.env = envp;
	builtin->home_path = getenv("HOME");
	set_envlist(&data, &builtin->env_list);
	if (prompt(&data, builtin))
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