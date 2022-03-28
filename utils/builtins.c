#include "../minishell.h"

int	check_if_builtin(t_package *head)
{
	if (cmd_variants(head->cmd, "echo", ft_strlen("echo")))
		return (1);
	if (cmd_variants(head->cmd, "cd", ft_strlen("cd")))
		return (1);
	else if (cmd_variants(head->cmd, "pwd", ft_strlen("pwd")))
		return (1);
	else if (cmd_variants(head->cmd, "export", ft_strlen("export")))
		return (1);
	else if (cmd_variants(head->cmd, "unset", ft_strlen("unset")))
		return (1);
	else if (cmd_variants(head->cmd, "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(head->cmd, "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

int check_for_flag(char *str, bool *flag) //TODO-> muss noch für andere flags ausgebaut werden
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '-')
		{
			index++;
			if ((str[index] == 'n' && str[index+1] == 'n') || str[index + 1] == '\0')
			{
				(*flag) = true;
				return (1);
			}
			else
				return (0);
		}
		index++;
	}
	return (0);
}

int	builtin_picker(t_package *package, t_builtin *builtin, char ***env_cpy)
{
	bool	flag;
	int		exit_state;

	flag = false;
	exit_state = 0;
	if (!package)
		return (0);
	if (cmd_variants(package->cmd_args[0], "echo", ft_strlen("echo")))
	{
		exit_state = prep_echo(package, flag);
		return (exit_state);
	}
	else if (cmd_variants(package->cmd_args[0], "cd", ft_strlen("cd")))
		exit_state = prep_cd(package, builtin);
	else if (cmd_variants(package->cmd_args[0], "pwd", ft_strlen("pwd")))
		exit_state = call_pwd(1);
	else if (cmd_variants(package->cmd_args[0], "env", ft_strlen("env")))
		exit_state = print_env(builtin);
	else if (cmd_variants(package->cmd_args[0], "unset", ft_strlen("unset")))
		exit_state = ft_unset(&builtin->env_list, package->cmd_args[1], env_cpy);
	else if (cmd_variants(package->cmd_args[0], "export", ft_strlen("export")))
	{
		if (package->cmd_args[1] == NULL)
		{
			print_export(builtin);
			return (1);
		}
		exit_state = ft_export(&builtin->env_list, package, env_cpy);
	}
	else if (!ft_strncmp(package->cmd_args[0], "exit", ft_strlen("exit")))
	{
		ft_exit(package);
	}
	if (exit_state == 1)
		g_exit_stat = 0;
	else
		g_exit_stat = 1;
	printf("exit_state %d\n", exit_state);
	return (0);
}
