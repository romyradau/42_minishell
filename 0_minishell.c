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
		else if (input[0] == 0)
		{
			write(2, "no input\n", 10);
			write(2, "fix input handling\n", 21);

			return (1);
		}
		return (0);
}

int	execute_print(t_package *head)
{
	printf("execute print: cmd = %s\n", head->cmd);
	if (cmd_variants(head->cmd, "echo", ft_strlen("echo")))
		return (1);
	if (cmd_variants(head->cmd, "cd", ft_strlen("cd")))
		return (1);
	else if (cmd_variants(head->cmd, "pwd", ft_strlen("pwd")))
		return (1);
	else if (cmd_variants(head->cmd, "export", ft_strlen("export")))
		return (1);
	else if (cmd_variants(head->cmd, "unset", ft_strlen("unset")))
		return (1);
	else if (cmd_variants(head->cmd, "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(head->cmd, "exit", ft_strlen("exit")))
		return (1);
	return (0);
}


int	prompt(t_data *data, t_builtin *builtin)
{
	char	*input;
	char	*user;

	struct	termios termios_p;

	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = SA_RESTART;
	data->sa.sa_handler = btn_handler;
	//TODO eigene function

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	while (1)
	{
		sigaction(SIGQUIT, &data->sa, NULL);
		sigaction(SIGINT, &data->sa, NULL);
		//TODO eigene function
		input = readline(user);
		if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
			return (-1);
		termios_p.c_lflag &= ~(ECHOCTL); //this will hinder echoing controll chars beck to the terminal
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
			return (-1);

		if (empty_input(input))
			return (1);
			printf("1\n");
		// prep_signal(data);
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
		//glaub das geschieht intern
		print2Darray(data->processes);
		process_packages(data, builtin);
		/* end parsing */

		/* start execution */
		/* end execution and print the right stuff*/
		if (execute_print(data->head))
			data->head = print_package_builtin(data->head, builtin);
		else
			data->head =  print_package_normal(data->head, builtin);
		add_history(input);
		free(input);
		if (termios_p.c_lflag & ECHOCTL)
			termios_p.c_lflag |= ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
			return (-1);
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
	g_exit_stat = 0;
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