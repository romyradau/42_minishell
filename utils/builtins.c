#include "../minishell.h"

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ unset with no options
◦ export with no options
◦ env with no options or arguments - getenv
◦ exit with no options - exit
*/



int check_for_flag(char *str, bool *flag) //TODO-> muss noch für andere flags ausgebaut werden
{
	int index;
	
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '-')
		{
			index++;
			if (str[index] == 'n')
			{
				(*flag) = true;
				return (1);
			}
			else
				return (0);
		}
		index++;
	}
	return (0);
}

int builtin_picker(t_package *package, t_builtin *builtin)
{
	bool	flag;
	char	**output;
	int		exit_state;

	flag = false;
	output = NULL;
	exit_state = 0;
	if (!package)
		return (0);
	ft_putendl_fd(package->cmd_args[0], 2);
	
	if (cmd_variants(package->cmd_args[0], "echo", ft_strlen("echo")))
	{
		exit_state = prep_echo(package, flag);
		return (exit_state);
	}
	else if (cmd_variants(package->cmd_args[0], "cd", ft_strlen("cd")))
		exit_state = prep_cd(package, builtin);
	else if (cmd_variants(package->cmd_args[0], "pwd", ft_strlen("pwd")))
		exit_state = call_pwd(1);
	else if (cmd_variants(package->cmd_args[0], "env", ft_strlen("env")))
		exit_state = print_env(builtin);
	else if (cmd_variants(package->cmd_args[0], "unset", ft_strlen("unset")))
		exit_state = ft_unset(&builtin->env_list, package->cmd_args[1]);
	else if (cmd_variants(package->cmd_args[0], "export", ft_strlen("export")))
	{
		if (package->cmd_args[1] == NULL)
			return (0);
		exit_state = ft_export(&builtin->env_list, package);
	}
	else if (!ft_strncmp(package->cmd_args[0], "exit", ft_strlen("exit")))
	{
		if (package->cmd_args != NULL)
			kill_d_str(package->cmd_args);
		else if (package->cmd_args[2])
		{
			printf("bash: exit: too many arguments\n");
			g_exit_stat = 1;
			return (0);
		}
		exit(0);
	}
	if (exit_state == 1)
		return (1);
	g_exit_stat = 127;
    return (0);
}
