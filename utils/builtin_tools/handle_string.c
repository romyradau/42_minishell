#include "../../minishell.h"

char *ft_strcalloc(int size)
{
	char *new_s;
	int i;

	new_s = malloc(size);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < size)
		new_s[i++] = 0;
	return (new_s);
}

int doublestr_len(char **cmd_arg)
{
	int i;
	int j;
	int s_t;

	i = 0;
	j = 0;
	s_t = 0;
	while (cmd_arg[i])
	{
		j = 0;
		while (cmd_arg[i][j])
			j++;
		s_t += j;
		i++;
	}
	return (s_t);
}

void	kill_d_str(char **str)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (str[len] == NULL)
	{
		return ;
	}
	while (str[len] != NULL)
		len++;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int ft_d_strlen(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char *get_path(char **env, const char *search_str)
{
	int	start_len;
	int	i;
	char *path;


	start_len = 0;
	i = 0;
	while(env[i] != NULL)
	{
		if(!ft_strncmp(env[i], search_str, ft_strlen(search_str)))
		{
			printf("env stirng[%d]: %s\n", i, &env[i][4]);
			while (env[i][start_len] != '=')
				start_len++;
			start_len++;
			path = ft_strdup(&env[i][start_len]);
			printf("path: %s\n", path);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int env_list_len(t_envlist *list)
{
	int i;

	i = 0;
	while (list->next != NULL)
	{
		i++;
		list = list->next;
	}
	return (i + 1);
}

void set_new_env(char ***cpy_envp, t_envlist *env_list)
{
	int i;
	int size;

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

int update_new_env(char ***cpy, t_envlist	*envlist)
{
	if ((*cpy) != NULL)
	{
		printf("%p\n", cpy);
		kill_d_str((*cpy));
	}
	(*cpy) = ft_calloc(env_list_len(envlist) + 1, sizeof(char *));
	if (!(*cpy))
		return (0);
	set_new_env(cpy, envlist);
	return (1);
}

char **cut_from_path(t_data *data, t_package *package)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (data->env[i])
	{
		printf("cmd_arg[%d]:%s\n", 1, package->cmd_args[1]);
		if (!ft_strncmp(data->env[i], package->cmd_args[1], ft_strlen(package->cmd_args[1])))
		{
			// int tmp_cnt = i;
			printf("to cut %s, found: %s\n", package->cmd_args[1], data->env[i]);
			while (data->env[i][j] == package->cmd_args[1][j])
				j++;
			printf("(new)data->env%d:%s\n", i, &data->env[i][j]);
			if (ft_strlen(data->env[i]) == ft_strlen(package->cmd_args[1]))
			{
				int size = ft_d_strlen(data->env);
				while (i < size)
				{
					data->env[i] = ft_strdup(data->env[i+1]);
					i++;
				}
				return (data->env);
			}
			tmp = ft_strdup(&data->env[i][j]);
			// free(data->env[i]);
			// data->env[i] = 0;
			data->env[i] = ft_strdup(tmp);
			// free(tmp);
			return (data->env);
		}

		i++;
	}
	return (NULL);
}