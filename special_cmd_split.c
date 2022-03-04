#include "minishell.h"

static int	ft_findW_count(char const *s, char c)
{
	int		i;
	int	quotes = 1;
	int	cnt;

	i = 0;
	cnt = 1;
	while (s[i] != '\0')
	{
		while ((s[i] != c || quotes == -1) && s[i] != '\0')
 		{
			if (s[i] == '@')
				quotes *= -1;
			i++;
		}
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
	}
	if (quotes == -1)
	{
		printf("SSS\n");
		return (-1);
	}
	return (cnt);
}

static int	ft_count(int cnt, char const *str, char c)
{
	int	i;
	int	quotes = 1;


	i = cnt;
	while ((str[i] == c) && (str[i] != '\0') && quotes == 1)
	{

		if (str[i] == '@')
			quotes *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

static int	ft_count_toNext(int cnt, char const *str, char c)
{
	int	i;
	int	quotes = 1;


	i = cnt;
	while (((str[i] != c) && (str[i] != '\0')) || (quotes == -1))
	{
		if (str[i] == '@')
			quotes *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

// void	change_result(char **result)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = NULL;
// 	while (result[i])
// 	{
// 		if (result[i][j] == '@')
// 		{
// 			printf("result  %s\n", result[i]);
// 			tmp = result[i];
// 			free(result[i]);
// 			result[i] = ft_strtrim(tmp, "@");
// 			free(tmp);
// 		}
// 	i++;
// 	}
// 	result[i] = NULL;
// }
//des in @ wird nicht mehr erkannt


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
	// change_result(result);
	// result[i] = NULL;
	return (result);
}
