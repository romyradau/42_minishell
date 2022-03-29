/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cmd_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:29:13 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 22:29:15 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	you_are_my_desire(const char *str, char c, int *i, int *cnt)
{
	while (str[(*i)] == c)
			(*i)++;
	if (str[(*i)] != '\0')
			(*cnt)++;
}

int	ft_find_cmd(char const *s, char c)
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
			if (s[i] == -2 && sq == 1)
				dq *= -1;
			if (s[i] == -1 && dq == 1)
				sq *= -1;
			i++;
		}
		you_are_my_desire(s, c, &i, &cnt);
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
		if (str[i] == -2 && sq == 1)
			dq *= -1;
		if (str[i] == -1 && dq == 1)
			sq *= -1;
		i++;
	}
	cnt = i;
	return (cnt);
}

static int	ft_count_to_next(int cnt, char const *str, char c)
{
	int	i;
	int	dq;
	int	sq;

	dq = 1;
	sq = 1;
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

	if (help(s, &start, &i, c) == -1)
		return (NULL);
	result = (char **)ft_calloc((help(s, &start, &i, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (int)ft_find_cmd(s, c) && ft_find_cmd(s, c) != 0)
	{
		start = ft_count(start, s, c);
		end = ft_count_to_next(start, s, c);
		result[i] = ft_substr(s, start, end - start);
		i++;
		start = end;
	}
	result[i] = NULL;
	return (result);
}
