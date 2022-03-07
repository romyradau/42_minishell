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
		while (cmd_arg[i][j])
			j++;
		s_t += j;
		i++;
	}
	return (s_t);
}

char **kill_d_str(char **str)
{
	char **tmp;
	int len;
	int i;

	tmp = str;
	len = 0;
	i = 0;
	while (*tmp)
	{
		tmp++;
		len++;
	}
	while (i < len)
	{
		str[i] = ft_strcalloc(1);
		i++;	
	}
	free(str);
	return (str);
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