
#include "../minishell.h"

int call_pwd(int fd)
{
	char cur_dir[10000];
	(void)fd;
	if (!getcwd(cur_dir, sizeof(cur_dir)))
		return (0);	
	ft_putstr_fd(cur_dir, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}

int prep_cd(t_package *package, t_builtin *builtin)
{

	int		i;
	
	i = 1;
	if (package->cmd_args[i] == NULL)
	{
		if (chdir(builtin->home_path) != 0)
			return (0);
		return (1);
	}
	if (!ft_strncmp(package->cmd_args[i], "..", 2) || !ft_strncmp(package->cmd_args[i], "-", 1))
	{
		if (chdir("..") != 0)
			return (0);
		return (1);
	}
	else if (ft_strncmp(package->cmd_args[i], "..", 2))
	{
		if (chdir(package->cmd_args[i]) != 0)
		{
			printf("cd: %s:  no such file or directory\n", package->cmd_args[1]);
			g_exit_stat = 1;
			return (0);
		}
		return (1);
	}
	return (1);
}