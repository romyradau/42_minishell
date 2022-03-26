
#include "../minishell.h"

int ft_exit(t_package *package)
{
    int i;

	i = 1;
	while (package->cmd_args[i] != NULL)
	{
		if (ft_isalpha(package->cmd_args[i][0]))
		{
			printf("is invalid: %s, %c\n", package->cmd_args[i], package->cmd_args[i][0]);
			return (0);
		}
		else if (ft_atoi(package->cmd_args[i]) <= INT_MAX
			|| ft_atoi(package->cmd_args[i]) >= INT_MIN)
		{
			printf("minishell : exit: %d : numeric argument required\n", ft_atoi(package->cmd_args[i]));
			g_exit_stat = 255;
			exit(g_exit_stat);
		}
		i++;
	}
    printf("i : %d\n", i);
	if (package->cmd_args[1] == NULL)
		exit(0);
	else if (package->cmd_args[2] == NULL)
		exit(ft_atoi(package->cmd_args[1]));
	else if (package->cmd_args[2] != NULL)
	{
		printf("bash: exit: too many arguments\n");
		g_exit_stat = 1;
		return (0);
	}
    return (1);
}