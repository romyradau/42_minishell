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

	bool	quots;
	bool	flag;
	int		i;
	int		j;
	char **output;

	quots = false;
	flag = false;
	output = NULL;
	i = 1;
	j = 0;

	if (!package)
		return (0);
	while (package->next != NULL)
	{
		package = package->next;
	}
	if (cmd_variants(package->cmd_args[0], "echo", ft_strlen("echo")))
    {
		if (prep_echo(package, flag))
			return (1);
    }
	else if (cmd_variants(package->cmd_args[0], "cd", ft_strlen("cd")))
	{
		if (prep_cd(package, builtin))
			return (1);
	}
	else if (cmd_variants(package->cmd_args[0], "pwd", ft_strlen("pwd")))
	{
		if (call_pwd(1))
			return (1);
	}
	else if (cmd_variants(package->cmd_args[0], "env", ft_strlen("env")))
	{
		if (print_env(builtin))
			return (1);
	}
	else if (cmd_variants(package->cmd_args[0], "unset", ft_strlen("unset")))
	{
		if (package->cmd_args[1] == NULL)
			return (0);
		if (!ft_unset(&builtin->env_list, package->cmd_args[1]))
			return (1);
	}
	else if (cmd_variants(package->cmd_args[0], "export", ft_strlen("export")))
	{
		if (package->cmd_args[1] == NULL)
			return (0);
		else if (!ft_export(&builtin->env_list, package))
			return(0);
		
	}
	else if (!ft_strncmp(package->cmd_args[0], "exit", ft_strlen("exit")))
	{
		if (package->cmd_args != NULL)
			kill_d_str(package->cmd_args);
		exit(0);
	}
	g_exit_stat = 127;
    return (0);
}
