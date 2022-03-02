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
	// printf("+++++++++++++BUTILT_IN PICKER RUNS++++++++++++\n");
	if (!package)
		return (0);
	// package = pipe_case(package); //*this is for when pipes appear
	if (cmd_variants(package->cmd_args[0], "echo", ft_strlen("echo")))
    {
		if (prep_echo(package, flag))
		{
			// printf("+++++++++++++BUTILT_IN PICKER COMPLETED FOR ECHO++++++++++++\n");
			return (1);
		}
    }
	if (cmd_variants(package->cmd_args[0], "cd", ft_strlen("cd")))
	{
		// printf("\e[0;31m CD fialed here!\033[0m\n");
		if (prep_cd(package, builtin))
		{
			// printf("+++++++++++++BUTILT_IN PICKER COMPLETED FOR CD++++++++++++\n");
			return (1);
		}
	}
	if (cmd_variants(package->cmd_args[0], "pwd", ft_strlen("pwd")))
	{
		// printf("\e[0;31m CD fialed here!\033[0m\n");
		if (call_pwd(1))
		{
			// printf("+++++++++++++BUTILT_IN PICKER COMPLETED FOR CD++++++++++++\n");
			return (1);
		}
	}
	if (cmd_variants(package->cmd_args[0], "env", ft_strlen("env")))
	{
		if (print_env(builtin))
		{
			return (1);
		}
	}
	if (cmd_variants(package->cmd_args[0], "unset", ft_strlen("unset")))
	{
		printf("unset runs!\n");
		if (package->cmd_args[1] == NULL)
			return (0);
		if (!ft_unset(&builtin->env_list, package->cmd_args[1]))
			return (1);
		else
			return (0);
	}

	// printf("+++++++++++++BUTILT_IN PICKER FAILED++++++++++++\n");
    return (0);
}
