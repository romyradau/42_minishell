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


void	free_all_nodes(t_data *data)
{
	t_package *tmp;
	int		i;

	i = 0;
	while (data->head != NULL)
	{
		tmp = data->head;
		while (tmp->cmd_args && tmp->cmd_args[i] != NULL)
		{
			free(tmp->cmd_args[i]);
			i++;
		}
		if (tmp->cmd_args)
			free(tmp->cmd_args);
		i = 0;
		while (tmp->infiles && tmp->infiles[i] != NULL)
		{
			free(tmp->infiles[i]);
			i++;
		}
		if (tmp->in_redirection)
			free(tmp->in_redirection);
		if (tmp->infiles)
			free(tmp->infiles);
		i = 0;
		while (tmp->outfiles && tmp->outfiles[i] != NULL && tmp->outfiles[i][0] != '\0')
		{
			free(tmp->outfiles[i]);
			i++;
		}
		if (tmp->out_redirection)
			free(tmp->out_redirection);
		if (tmp->outfiles)
			free(tmp->outfiles);
		free(tmp);
		data->head = data->head->next;
	}
}

int	prompt(t_data *data, t_builtin *builtin, char **envp)
{
	
	char	*user;
	pid_t	pid;

	t_file	*file;
	char	*input;
	(void)envp;

	pid = getpid();
	//TODO eigene function
	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		set_attr();
		//TODO eigene function
		input = readline(user);
		errno = 0;
		// prep_signal(data);
		if (empty_input(input))
		{
				/* start parsing */
			data->processes = special_pipe_split(input, '|');
			//freen?
			if (!data->processes)
				return (1);
			data->processes = trim_spaces(data);
			//protecten??
			//glaub das geschieht intern
			// print2Darray(data->processes);
			if (!process_packages(data, builtin))
			{
				unset_attr();
				file = init_redirections();
			    /* end execution and print the right stuff*/
				add_history(input);
				if (check_if_builtin(data->head) && data->head->next == NULL)
				{

					perror("GENARAL1: ");
					rechts(file, data->head);
					perror("GENARAL2: ");
					links(file, data->head);
					perror("GENARAL3: ");
					builtin_picker(data->head, builtin);
					dup2(file->out, 1);
					dup2(file->in, 0);
					close(file->tmp_fd);
					close(file->in);
					close(file->out);
				}
				else
  					execute_function(data, envp, builtin, file);
				
			}
			else
				kill_d_str(data->processes);
			// free(input);
			/* besser machen */
			// data->head = NULL;
			free_all_nodes(data);
			// if (termios_p.c_lflag & (ECHOCTL))/* besser machen */
			// 	termios_p.c_lflag |= ~(ECHOCTL);
			// if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == -1)
				// return (-1);
			
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
	(void)argv;
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