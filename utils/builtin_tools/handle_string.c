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