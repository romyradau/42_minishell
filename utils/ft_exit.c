
#include "../minishell.h"

static int	ft_exit_valid(t_package *pack, int i)
{
	if (ft_isalpha(pack->cmd_args[i][0]))
	{
		printf("is invalid: %s, %c\n", pack->cmd_args[i],
			pack->cmd_args[i][0]);
		return (0);
	}
	else if ((pack->cmd_args[i][0] == '-'
		&& pack->cmd_args[i][1] == '-')
		|| (pack->cmd_args[i][0] == '+'
		&& pack->cmd_args[i][1] == '+'))
	{
		printf("minishel : exit: %s: numeric argument required\n",
			pack->cmd_args[i]);
		exit(255);
	}
	else
		return (1);
}

static void	handle_exit(t_package *pack)
{
	if (pack->cmd_args[1] == NULL)
		exit(0);
	else if (pack->cmd_args[2] == NULL)
		exit(ft_atoi(pack->cmd_args[1]));
	else if (pack->cmd_args[2] != NULL)
	{
		printf("bash: exit: too many arguments\n");
		g_exit_stat = 1;
	}
}

int	ft_exit(t_package *pack)
{
	int	i;

	i = 1;
	while (pack->cmd_args[i] != NULL)
	{
		if (ft_exit_valid(pack, i) == 0)
			return (0);
		else if (ft_atoi(pack->cmd_args[i]) >= INT_MAX
			|| ft_atoi(pack->cmd_args[i]) <= INT_MIN)
		{
			printf("minishell : exit: %d : numeric argument required\n",
				ft_atoi(pack->cmd_args[i]));
			g_exit_stat = 255;
			exit(g_exit_stat);
		}
		i++;
	}
	handle_exit(pack);
	if (g_exit_stat == 1)
		return (0);
	return (1);
}
