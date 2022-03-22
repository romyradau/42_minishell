
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
	// int j;
	// int ret;
	(void) package;
	i = 0;
	len = ft_d_strlen(output);
	if (!output[0])
	{
		printf("%s", "error");
		return ;
	}
	while (output[i][0] != 10)
	{	
		ft_putstr_fd(output[i], STDOUT_FILENO);
		if (i < (len-2))
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	kill_d_str(output);
}

t_package *echo_pipecase(t_package *package)
{

	if((package->pipe && package->next != NULL)
		&& cmd_variants(package->next->cmd, "echo", ft_strlen("echo")))
		package = package->next;
	return (package);
}

int	write_to_pipe(char **output, bool flag, t_file *file)
{
	int j;

	j = 0;
	(void)file;
	// if (pipe(file) == -1)
	// 	return (0);
	while (output[j])
	{
		write(STDOUT_FILENO, output[j], ft_strlen(output[j]));
		j++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	kill_d_str(output);
	return (1);

}

int prep_echo(t_package *package, bool flag)
{
	char	**output;
	int		i;
	int		j;
	bool	put_in_pipe;

	output = NULL;
	i = 1;
	j = 0;
	put_in_pipe = false;
	package = echo_pipecase(package);
	if (package->cmd_args[i] == NULL)
		return (0);
	output = (char **)malloc(doublestr_len(package->cmd_args) * sizeof(char *));
	if(!output)
		return (0);
	while (package->cmd_args[i])
	{
		if (!package->cmd_args[i])
		{
			printf("\n");//wird das benotigt?
			return (1);
		}
		while (check_for_flag(package->cmd_args[i], &flag) && package->cmd_args[i] != NULL)
			i++;
		output[j] = ft_strdup(package->cmd_args[i]);
		// fprintf(stderr, "output: %s\n", output[j]);
		j++;
		i++;
	}
	if (!flag)
		output[j] = ft_strdup("\n");
	ft_echo(output, flag, package);
	return (1);
}