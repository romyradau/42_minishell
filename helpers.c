/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:22:24 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 21:37:14 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	helper(char const *s, int *start, int *i, char c)
{
	int		numberstrings;

	if (!s)
		return (-1);
	(*start) = 0;
	(*i)= 0;
	numberstrings = ft_find_cmd(s, c);
	if (numberstrings == -1)
		return (-1);
	return (numberstrings);
}

int	help(char const *s, int *start, int *i, char c)
{
	int		numberstrings;

	if (!s)
		return (-1);
	(*start) = 0;
	(*i)= 0;
	numberstrings = ft_find_pipe(s, c);
	if (numberstrings == -1)
		return (-1);
	return (numberstrings);
}
