
#include "../minishell.h"

int print_env(t_data *data, int fd)
{
    int i;

    i = 0;
    if (!data->env)
        return (0);
    while (data->env[i] != NULL)
    {
        ft_putstr_fd(data->env[i], fd);
        i++;
    }
    return (1);
}

// int ft_export();