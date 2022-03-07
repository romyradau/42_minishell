
#include "../minishell.h"

int ft_export(t_envlist **head, t_package *package)
{
    if (add_node(head, package->cmd_args[1]))
        return (0);
    return (1);

}