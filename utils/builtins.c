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

int check_quot_sequence(char *str, char c, bool *q)
{
    int i;

    i = 0;
    if (str[i] == c)
    {
		(*q) = true;
		// printf("bool %d\n", (*q));
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

// char	*fuse_quots_sequence(char **cmd_arg, bool flage)
// {
// 	char	*tmp_output;
// 	char	*output;
// 	int		i;

// 	tmp_output = NULL;
// 	output = NULL;
// 	if (flage)
// 		i = 2;
// 	else
// 		i = 1;
// 	if (!cmd_arg[i] || !cmd_arg[i + 1])
// 		return (NULL);
// 	tmp_output = ft_strjoin(cmd_arg[i], cmd_arg[i + 1]);
// 	output = cut_quot_sequence(tmp_output, '"');
// 	free(tmp_output);
// 	return (output);

// }

int doublestr_len(char **cmd_arg)
{
    int i;
    int j;
    int s_t;

    i = 0;
    j = 0;
    s_t = 0;
    while (cmd_arg[i])
    {
        while (cmd_arg[i][j])
            j++;
        s_t += j;
        i++;
    }
    return (s_t);
}

char *handle_qouts(char **cmd_arg, int index)
{
	bool	quots;
	char	*output;

	output = NULL;	
	quots = false;
	if (check_quot_sequence(cmd_arg[index], '"', &quots))
	{
		output = cut_quot_sequence(cmd_arg[index], '"');
		quots = false;
	}
	else if (!check_quot_sequence(cmd_arg[index], '"', &quots))
	{
		if (quots)
		{
			printf("error!\n");
			return (NULL);
		}
		else
		{
			output = (char *)malloc(ft_strlen(cmd_arg[index]) * sizeof(char));
			if (!output)
				return (0);
			output = cmd_arg[index];
		}

	}
	return (output);
}

void	ft_echo(char **output, bool flag)
{
	int i;

	i = 0;
	if (!output)
		printf("%s", "error");
	while (output[i])
	{
		printf("%s ", output[i]);
		i++;
	}
	if (!flag)
		printf("\n");
}

int builtin_picker(t_package *package)
{

	char	**cmd_arg;
	bool	quots;
	bool	flag;
	int		i;
	int		j;
	char **output;

	quots = false;
	flag = false;
	i = 1;
	j = 0;
	cmd_arg = package->cmd_args;
	output = (char **)malloc(doublestr_len(cmd_arg) * sizeof(char *));
	if(!output)
		return (0);
	if (!ft_strncmp(cmd_arg[0], "echo", doublestr_len(cmd_arg)))
    {
		while (cmd_arg[i])
		{
			if (!ft_strncmp(cmd_arg[i], "-n", doublestr_len(cmd_arg)))
			{
				i++;
				flag = true;
			}
			// handle qoutos
			output[j] = handle_qouts(cmd_arg, i);
			//run echo
			i++;
			j++;
		}
		output[i + 1] = "\0";
        ft_echo(output, flag);
        return (1);
    }
    return (0);
}
