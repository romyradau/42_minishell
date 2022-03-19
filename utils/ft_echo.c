
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
	int ret;

	i = 0;
	len = ft_d_strlen(output);
	ret = 0;
	if (*package->out_redirection == 2)
	{
		ret = open(*package->outfiles, O_CREAT | O_WRONLY);
		if (ret < 0)
			return ;
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

t_package *echo_pipecase(t_package *package, bool *put_in_pipe)
{
	if((package->pipe && package->next != NULL)
		&& cmd_variants(package->next->cmd, "echo", ft_strlen("echo")))
		package = package->next;
	else if (package->pipe && package->next != NULL
		&& !check_if_builtin(package))
	{
		(*put_in_pipe) = true;
		return (package);
	}
	return (package);
}

int	write_to_pipe(t_package *package, char **output, bool flag)
{
	int j;

	j = 0;
	printf("the output will be wrote in to the pipe!\n");
	if (pipe(package->redir->fd) == -1)
		return (0);
	while (output[j])
	{
		write(package->redir->fd[1], output[j], ft_strlen(output[j]));
		j++;
	}
	if (!flag)
		write(package->redir->fd[1], "\n", 1);
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

	package = echo_pipecase(package, &put_in_pipe);
	if (package->cmd_args[i] == NULL)
	{
		printf("prep echo exits\n");
		return (0);
	}
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
		output[j] = ft_strdup(package->cmd_args[i]);
		j++;
		i++;
	}
	output[j] = ft_strdup("\n");
	if (put_in_pipe)
		write_to_pipe(package, output, flag);
	else
		ft_echo(output, flag, package);
	return (1);
}