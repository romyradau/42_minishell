/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_pipe_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:21:15 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 23:12:27 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	taste_of_my_lips(const char *s, char c, int *i, int *cnt)
{
	while (s[(*i)] == c)
	{
		(*i)++;
		if (s[(*i)] == c)
			return ((*cnt));
	}
	if (s[(*i)] != '\0')
		(*cnt)++;
	return (-1);
}

int	ft_find_pipe(char const *s, char c)
{
	int		i;
	int		dq;
	int		sq;
	int		cnt;

	i = 0;
	cnt = 1;
	dq = 1;
	sq = 1;
	while (s[i] != '\0')
	{
		while ((s[i] != c || sq == -1 || dq == -1) && s[i] != '\0')
		{
			if (s[i] == '"' && sq == 1)
				dq *= -1;
			if (s[i] == '\'' && dq == 1)
				sq *= -1;
			i++;
		}
		if (taste_of_my_lips(s, c, &i, &cnt) != -1)
			return (cnt);
	}
	if (sq == -1 || dq == -1)
		return (-1);
	return (cnt);
}

static int	ft_count(int cnt, char const *str, char c)
{
	int	i;
	int	dq;
	int	sq;

	sq = 1;
	dq = 1;
	i = cnt;
	while ((str[i] == c) && (str[i] != '\0') && sq == 1 && dq == 1)
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

static int	ft_count_tonext(int cnt, char const *str, char c)
{
	int	i;
	int	dq;
	int	sq;

	dq = 1;
	sq = 1;
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

char	**special_pipe_split(char const *s, char c)
{
	char	**result;
	int		start;
	int		end;
	int		i;

	if (helper(s, &start, &i, c) == -1)
		return (NULL);
	result = (char **)malloc((helper(s, &start, &i, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (int)ft_find_pipe(s, c) && ft_find_pipe(s, c) != 0)
	{
		start = ft_count(start, s, c);
		end = ft_count_tonext(start, s, c);
		result[i] = ft_substr(s, start, end - start);
		i++;
		start = end;
	}
	result[i] = NULL;
	return (result);
}
