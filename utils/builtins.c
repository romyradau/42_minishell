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



int check_for_flag(char *str) //TODO-> muss noch für andere flags ausgebaut werden
{
	int index;
	
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '-')
		{
			index++;
			if (str[index] == 'n')
				return (1);
			else
				return (0);
		}
		index++;
	}
	return (0);
}

int builtin_picker(t_package *package)
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
	printf("+++++++++++++BUTILT_IN PICKER RUNS++++++++++++\n");
	if (!package)
		return (0);
	// package = pipe_case(package); //*this is for when pipes appear
	if (echo_variants(package->cmd_args[0], "echo", ft_strlen("echo")))
    {
		if (prep_echo(package))
			return (1);
    }
    return (0);
}
