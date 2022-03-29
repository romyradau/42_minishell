#include "../../minishell.h"

char	*ft_strcalloc(int size)
{
	char	*new_s;
	int		i;

	new_s = malloc(size);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < size)
		new_s[i++] = 0;
	return (new_s);
}

int	doublestr_len(char **cmd_arg)
{
	int	i;
	int	j;
	int	s_t;

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

int	ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if ((int) ft_strlen(str) == i || i == 0)
		return (0);
	return (i);
}