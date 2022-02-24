#include "minishell.h"

int	ft_findW_count(char const *s, char c)
{
	int	i = 0;
	int	cnt = 1;
	int	dq = 1;
	int	sq = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c || sq == -1 || dq == -1)
		{
			if (s[i] == '"' && sq == 1)
				dq *= -1;
			if (s[i] == '\'' && dq == 1)
				sq *= -1;
			cnt++;
			while ((s[i] != c || sq == -1 || dq == -1) && s[i] != '\0')
				i++;
		}
		if (c == s[i] && sq == 1 && dq == 1)
			while ((c == s[i] && sq == 1 && dq == 1) && s[i] != '\0')
				i++;
		i++;
	}
	if (sq == -1 || dq == -1)
		return (-1);
	return (cnt);
}


static int	ft_count(int cnt, char const *str, char c)
{
	int	i;
	int	dq = 1;
	int	sq = 1;

	i = cnt;
	while ((str[i] == c) && (str[i] != '\0') && sq == 1 && dq == 1)
	//wenn des ne legit pipe ist dann gehma weiter
	{
		if (str[i] == '"' && sq == 1)
			dq *= -1;
		if (str[i] == '\'' && dq == 1)
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
		if (str[i] == '"' && sq == 1)
			dq *= -1;
		if (str[i] == '\'' && dq == 1)
			sq *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

char	**special_split(char const *s, char c)
{
	char	**result;
	int	start;
	int	end;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	i = 0;

	int	numberStrings = ft_findW_count(s, c);
	if (numberStrings == -1)
		return (NULL); //error unclosed quotes
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