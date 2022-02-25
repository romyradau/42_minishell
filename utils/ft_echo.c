
#include "../minishell.h"

//TODO: Pipes, ($) not finished

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
		ft_putstr_fd(output[i], ret);
		if (ft_strncmp(output[i + 1], "\0", 1))
			write(ret, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	printf("%d\n", i);
	kill_d_str(output);
}

int prep_echo(t_package *package)
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
			if (!package->cmd_args[i])
			{
				printf("\n");
				return (1);
			}
			while (check_for_flag(package->cmd_args[i]) && package->cmd_args[i] != NULL)
			{
				i++;
				flag = true;
			}
			output[j] = handle_qouts(package->cmd_args, i);
			j++;
			i++;
		}
		output[j] = ft_strdup("\n");
		ft_echo(output, flag, package);
		printf("Pointer is freed\n");
		return (1);
	}
	return (0);
}