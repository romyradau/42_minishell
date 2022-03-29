/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_allocate_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:16:42 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 19:16:44 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_compare(char *current, t_red **red, int *i)
{
	if (double_quotes(current, red, i))
		(*i)++;
	if (single_quotes(current, red, i))
		(*i)++;
	return (in_or_out(current, i));
}

int	which_redirection(char *current, int *count, int *i)
{
	if (current[(*i)] == '<')
	{
		if (current[(*i) + 1] == '<')
			(*i)++;
		if (current[(*i) + 1] == '<' || current[(*i) + 1] == '>')
			return (-1);
		(*count)++;
	}
	else if (current[(*i)] == '>')
	{
		if (current[(*i) + 1] == '>')
			(*i)++;
		if (current[(*i) + 1] == '>' || current[(*i) + 1] == '<')
			return (-1);
		(*count)++;
	}
	return (0);
}

int	amount_redirections(char *current)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (current[i])
	{
		skip_dq(current, &i);
		skip_sq(current, &i);
		if (which_redirection(current, &count, &i) == -1)
			return (-1);
		i++;
	}
	return (count);
}

int	allocate_redirections(t_package **newNode, char *current)
{
	int	amount_red;

	amount_red = amount_redirections(current);
	(*newNode)->outfiles = ft_calloc(amount_red + 1, sizeof(char *));
	(*newNode)->infiles = ft_calloc(amount_red + 1, sizeof(char *));
	(*newNode)->out_redirection = ft_calloc(amount_red + 1, sizeof(int));
	(*newNode)->in_redirection = ft_calloc(amount_red + 1, sizeof(int));
	return (amount_red);
}
