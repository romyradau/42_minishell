#include "../../minishell.h"

char	*get_path(char **env_cpy, const char *search_str)
{
	int		start_len;
	int		i;
	char	*path;

	start_len = 0;
	i = 0;
	path = NULL;
	while (env_cpy[i] != NULL)
	{
		if (!ft_strncmp(env_cpy[i], search_str, ft_strlen(search_str)))
		{
			while (env_cpy[i][start_len] != '=')
				start_len++;
			start_len++;
			path = ft_strdup(&env_cpy[i][start_len]);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	env_list_len(t_envlist *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	set_new_env(char ***cpy_envp, t_envlist *env_list)
{
	int	i;
	int	size;

	size = env_list_len(env_list);
	i = 0;
	while (env_list->next != NULL)
	{
		(*cpy_envp)[i] = ft_strdup(env_list->content);
		i++;
		env_list = env_list->next;
	}
	if (env_list->next == NULL)
	{
		(*cpy_envp)[i] = ft_strdup(env_list->content);
	}
}

int	update_new_env(char ***cpy, t_envlist	*envlist)
{
	if ((*cpy) != NULL)
	{
		kill_d_str((*cpy));
	}
	(*cpy) = ft_calloc(env_list_len(envlist) + 1, sizeof(char *));
	if (!(*cpy))
		return (0);
	set_new_env(cpy, envlist);
	return (1);
}
