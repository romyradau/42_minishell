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
			return (0);
		return (1);
}

int	check_if_builtin(t_package *head)
{
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


int	prompt(t_data *data, t_builtin *builtin, char **envp)
{
	char	*input;
	char	*user;
	pid_t	pid;
	struct	termios termios_p;

	(void)envp;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = SA_RESTART;
	data->sa.sa_handler = btn_handler;
	pid = getpid();
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
		termios_p.c_lflag &= ~(ECHOCTL); //this will enable echoing controll chars beck to the terminal
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
			return (-1);

		// prep_signal(data);
		if (empty_input(input))
		{
				/* start parsing */
				data->processes = special_pipe_split(input, '|');
			//freen?
			if (!data->processes)
			{
				printf("error: unclosed quotes\n");
				return (1);
				//TODO: muss noch gehandelt werden, dass die message bei quit mit ctrl D weggeht
			}
			data->processes = trim_spaces(data);
			//protecten??
			//glaub das geschieht intern
			// print2Darray(data->processes);
			if (!process_packages(data, builtin))
			{

			    /* end execution and print the right stuff*/
				//   if (execute_print(data->head))
				// 	  data->head = print_package_builtin(data->head, builtin);
				//   else
				// 	  data->head =  print_package_normal(data->head, builtin);
				add_history(input);
				if (check_if_builtin(data->head) && data->head->next == NULL)
					builtin_picker(data->head, builtin);
				else
  					execute_function(data, envp, builtin);
			}
			else
				kill_d_str(data->processes);
			free(input);
			termios_p.c_lflag |= ECHOCTL;
			if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
				return (-1);
		}
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
	builtin->env_list = NULL;
	(void) argc;
	(void) argv;
	g_exit_stat = 0;
	ft_bzero(&data, sizeof(t_data));
	data.env = envp;
	builtin->home_path = getenv("HOME");
	set_envlist(&data, &builtin->env_list);
	if (prompt(&data, builtin, envp))
		return(1);
	return (0);
}

/*
main = introduction of t_data & stores env & sends to->
prompt = readline & packages vorbereiten
process_packages = pusht die packages & setzt den pipe bool fur alle packages
*/