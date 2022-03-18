#include "minishell.h"

static int	ft_findW_count(char const *s, char c)
{
	int		i;
	int		dq = 1;
	int		sq = 1;
	int	cnt;

	i = 0;
	cnt = 1;
	while (s[i] != '\0')
	{
		while ((s[i] != c || sq == -1 || dq == -1) && s[i] != '\0')
 		{
			if (s[i] == -2 && sq == 1)
				dq *= -1;
			if (s[i] == -1 && dq == 1)
				sq *= -1;
			i++;
		}
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
	}
	if (sq == -1 || dq == -1)
	{
		return (-1);
	}
	return (cnt);
}

static int	ft_count(int cnt, char const *str, char c)
{
	int	i;
	int	dq = 1;
	int	sq = 1;


	i = cnt;
	while ((str[i] == c) && (str[i] != '\0') && sq == 1 && dq == 1)
	{
		if (str[i] == -2 && sq == 1)
			dq *= -1;
		if (str[i] == -1 && dq == 1)
			sq *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

static int	ft_count_toNext(int cnt, char const *str, char c)
{
	int	i;
	int	dq = 1;
	int	sq = 1;


	i = cnt;
	while (((str[i] != c) && (str[i] != '\0')) || (sq == -1 || dq == -1))
	{
		if (str[i] == -2 && sq == 1)
			dq *= -1;
		if (str[i] == -1 && dq == 1)
			sq *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

char	**special_cmd_split(char const *s, char c)
{
	char	**result;
	int		start;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	i = 0;
	int	numberStrings = ft_findW_count(s, c);
	if (numberStrings == -1)
		return (NULL);
	result = (char **)malloc((numberStrings + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (int)ft_findW_count(s, c) && ft_findW_count(s, c) != 0)
	{
		start = ft_count(start, s, c);
		end = ft_count_toNext(start, s, c);
		result[i] = ft_substr(s, start, end - start);
		i++;
		start = end;
	}
	result[i] = NULL;
	return (result);
}
