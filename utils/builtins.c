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

//TODO: fix segfault for -n -n case

char *ft_strcalloc(int size)
{
    char *new_s;
    int i;

    new_s = malloc(size);
    if (!new_s)
        return (NULL);
    i = 0;
    while (i < size)
        new_s[i++] = 0;
    return (new_s);
}

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
	if (check_quot_sequence(cmd_arg[index], '"', &quots) || check_quot_sequence(cmd_arg[index], 39, &quots))
	{
		if (check_quot_sequence(cmd_arg[index], 39, &quots))
			output = cut_quot_sequence(cmd_arg[index], 39);
		else if (check_quot_sequence(cmd_arg[index], '"', &quots))
			output = cut_quot_sequence(cmd_arg[index], '"');
		quots = false;
	}
	else if (!check_quot_sequence(cmd_arg[index], '"', &quots) || check_quot_sequence(cmd_arg[index], 39, &quots))
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

int echo_variants(char *str, const char *str2, unsigned int len)
{
	unsigned int i;

	i = 0;
	while (str[i] && (i <= len))
	{

		if (str[i] == str2[i])
			i++;
		else if (str[i] == ft_toupper(str2[i]))
			i++;
		else
			break ;
	}
	if (i == len)
		return (1);
	return (0);
	
}

t_package *pipe_case(t_package *package)
{
	int i;

	i = 0;
	if (package->next)
	{
		while (package->next)
		{
			if (echo_variants(package->next->cmd, "echo", ft_strlen("echo")))
				package = package->next;
			else
				break ;
		}
	}
	return (package);
}

char **kill_d_str(char **str)
{
	char **tmp;
	int len;
	int i;

	tmp = str;
	len = 0;
	i = 0;
	while (*tmp)
	{
		tmp++;
		len++;
	}
	while (i < len)
	{
		str[i] = ft_strcalloc(1);
		i++;	
	}
	free(str);
	return (str);
}

void	ft_echo(char **output, bool flag, t_package *package)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	printf("\n==========ECHO STARTS=======================\n");
	if (*package->out_redirection == 2)
	{
		printf("package has a redirection\n");
		ret = open(*package->outfiles, O_CREAT | O_WRONLY);
		if (ret < 0)
			return ;
		printf("file has been created: %s\n", *package->outfiles);
	}
	if (!output[0])
	{
		printf("%s", "error");
		return ;
	}
	while (output[i][0] != 10)
	{	
		// printf("output[i][0]%d\n", output[i][0]);
		// printf("[%d]output:%s\n", i, output[i]);
		ft_putstr_fd(output[i], ret);
		// if (ft_strncmp(output[i + 1], "\0", 1))
		// {	
		// 	printf("%s\n", output[i + 1]);
		write(ret, " ", 1);
		// }
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	printf("%d\n", i);
	kill_d_str(output);
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
		printf("\e[0;31m================ECHO is noted!======================\033[0m\n\e[0;34mcmd-> %s\033[0m\n", package->cmd_args[0]);
		output = (char **)malloc(doublestr_len(package->cmd_args) * sizeof(char *));
		if(!output)
			return (0);
		if (!package->cmd_args[i])
		{
			free(output);
			*output = 0;
			printf("\n");
			return (0);
		}
		while (package->cmd_args[i])
		{
			while (!ft_strncmp(package->cmd_args[i], "-n", doublestr_len(package->cmd_args)))
			{
				i++;
				flag = true;
				if (!package->cmd_args[i])
				{
					printf("\n");
					return (1);
				}
			}
			output[j] = handle_qouts(package->cmd_args, i);
			j++;
			i++;
		}
		output[j] = ft_strdup("\n");
        ft_echo(output, flag, package);
		printf("Pointer is freed\n");
		// package->cmd_args[0] = ft_strcalloc(1);
        return (1);
    }
    return (0);
}
