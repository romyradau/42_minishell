
#include "../minishell.h"

//TODO: ($) not finished

int cmd_variants(char *str, const char *str2, unsigned int len)
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
	int len;
	int ret;

	i = 0;
	len = ft_d_strlen(output);
	printf("len; %d\n", len - 1);
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
		if (i < (len-2))
			write(ret, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	kill_d_str(output);
}

t_package *echo_pipecase(t_package *package)
{
	if((package->pipe && package->next != NULL)
		&& cmd_variants(package->next->cmd, "echo", ft_strlen("echo")))
		package = package->next;
	return (package);
}

int prep_echo(t_package *package, bool flag)
{
	char	**output;
	int		i;
	int		j;

	output = NULL;
	i = 1;
	j = 0;

	package = echo_pipecase(package);
	if (!package->cmd_args[i])
		return (0);
	printf("\e[0;31m================ECHO is noted!======================\033[0m\n\e[0;34mcmd-> %s\033[0m\n", package->cmd_args[0]);
	output = (char **)malloc(doublestr_len(package->cmd_args) * sizeof(char *));
	if(!output)
		return (0);
	while (package->cmd_args[i])
	{
		if (!package->cmd_args[i])
		{
			printf("\n");
			return (1);
		}
		while (check_for_flag(package->cmd_args[i], &flag) && package->cmd_args[i] != NULL)
			i++;
		output[j] = handle_qouts(package->cmd_args, i);
		j++;
		i++;
	}
	output[j] = ft_strdup("\n");
	ft_echo(output, flag, package);
	return (1);
}