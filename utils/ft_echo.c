
#include "../minishell.h"

int	cmd_variants(char *str, const char *str2, unsigned int len)
{
	unsigned int	i;

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
	int	i;

	(void) package;
	i = 0;
	if (!output[0])
	{
		return ;
	}
	while (output[i])
	{	
		ft_putstr_fd(output[i], STDOUT_FILENO);
		if (output[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_stat = 0;
	kill_d_str(output);
	output = NULL;
}

int	check_if_empty(t_package *package, int i)
{
	if (package->cmd_args[i] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_stat = 0;
		return (1);
	}
	else if (package->cmd_args[i] != NULL
		&& !ft_strncmp(package->cmd_args[i], "-n", ft_strlen("-n"))
		&& package->cmd_args[i + 1] == NULL)
	{
		g_exit_stat = 0;
		return (1);
	}
	return (0);
}

int	prep_echo(t_package *package, bool flag)
{
	char	**output;
	int		i;
	int		j;

	output = NULL;
	i = 1;
	j = 0;
	if (check_if_empty(package, i) == 1)
		return (0);
	output = ft_calloc(doublestr_len(package->cmd_args) + 1, sizeof(char *));
	if (!output)
		return (0);
	while (package->cmd_args[i] != NULL
		&& check_for_flag(package->cmd_args[i], &flag))
		i++;
	while (package->cmd_args[i] != NULL)
	{
		output[j] = ft_strdup(package->cmd_args[i]);
		j++;
		i++;
	}
	ft_echo(output, flag, package);
	return (1);
}
