/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:25:43 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:38:31 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
cat <infile | bla      bla | wc -l       " "
1    2        1        2
*/
static size_t	ft_findw_cnt(char const *s, char c)
{
	int		i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			cnt++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static int	ft_cnt(int cnt, char const *str, char c)
{
	int	i;

	i = cnt;
	while ((str[i] == c) && (str[i] != '\0'))
		i++;
	cnt = i;
	return (cnt);
}

static int	ft_cnt_tonext(int cnt, char const *str, char c)
{
	int	i;

	i = cnt;
	while ((str[i] != c) && (str[i] != '\0'))
		i++;
	cnt = i;
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	cnt;
	size_t	cnt_2;
	int		i;

	if (!s)
		return (NULL);
	cnt = 0;
	i = 0;
	result = (char **)malloc((ft_findw_cnt(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (int)ft_findw_cnt(s, c) && ft_findw_cnt(s, c) != 0)
	{
		cnt = ft_cnt(cnt, s, c);
		cnt_2 = ft_cnt_tonext(cnt, s, c);
		result[i] = ft_substr(s, cnt, cnt_2 - cnt);
		i++;
		cnt = cnt_2;
	}
	result[i] = NULL;
	return (result);
}
