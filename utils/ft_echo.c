
#include "../minishell.h"

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

	(void) package;
	i = 0;
	if (!output[0])
	{
		return ;
	}
	while (output[i] && output[i][0] != 10)
	{	

		// printf("OUTPUT in FT_ECHO: %s\n", output[i]);
		ft_putstr_fd(output[i], STDOUT_FILENO);
		if (output[i+1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_stat = 0;
	kill_d_str(output);
	output = NULL;
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

	output = NULL;
	i = 1;
	j = 0;
	// package = echo_pipecase(package);
	if (package->cmd_args[i] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	output = ft_calloc(doublestr_len(package->cmd_args) + 2, sizeof(char *));
	if(!output)
		return (0);
	while (package->cmd_args[i] != NULL && check_for_flag(package->cmd_args[i], &flag))
		i++;
	while (package->cmd_args[i] != NULL)
	{
		// printf("HERE!\n");
		if (!package->cmd_args[i])
		{
			// printf("HERE IF!\n");
			printf("\n");//wird das benotigt?
			return (1);
		}
		// printf("i: %d\n",i);
		output[j] = ft_strdup(package->cmd_args[i]);
		// printf("i: %d\n",i);
		// printf("j: %d\n", j);
		j++;
		i++;
	}
	if (!flag)
		output[j] = ft_strdup("\n");
	ft_echo(output, flag, package);
	return (1);
}