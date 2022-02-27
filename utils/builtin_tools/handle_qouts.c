#include "../../minishell.h"

int check_quot_sequence(char *str, char c, bool *q)
{
    int i;

    i = 0;
    if (str[i] == c)
    {
		(*q) = true;
        i = ft_strlen(str)-1;
        if (str[i] == c)
            return (1);
    }
    return (0);
}

char    *cut_quot_sequence(char *str, char c)
{
    int     i;
	bool 	quots;
    char    *new_str;

    i = 1;
	quots = false;
    new_str = (char *)malloc(ft_strlen(str) * sizeof(char));
    if (str)
    {
        if (check_quot_sequence(str, c , &quots))
            new_str = ft_substr(str,1, ft_strlen(str) - 2);
        return (new_str);
    }
    else
        return (NULL);
}

char *handle_qouts(char **cmd_arg, int index)
{
	bool	quots;
	char	*output;

	output = NULL;	
	quots = false;
	if (check_quot_sequence(cmd_arg[index], '"', &quots) 
		|| check_quot_sequence(cmd_arg[index], 39, &quots))
	{
		if (check_quot_sequence(cmd_arg[index], 39, &quots))
			output = cut_quot_sequence(cmd_arg[index], 39);
		else if (check_quot_sequence(cmd_arg[index], '"', &quots))
			output = cut_quot_sequence(cmd_arg[index], '"');
		quots = false;
	}
	else if (!check_quot_sequence(cmd_arg[index], '"', &quots) 
		|| check_quot_sequence(cmd_arg[index], 39, &quots))
	{
		if (quots)
		{
			printf("error!\n");
			return (NULL);
		}
		else
		{
			printf("\nin handle_qouts : the string is allocated\n");
			output = ft_strdup(cmd_arg[index]);
			printf(".....\nAllocation is finished!\n");
		}

	}
	return (output);
}
