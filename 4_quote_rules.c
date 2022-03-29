/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_quote_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:56:54 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 19:56:54 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	skip_dq(char *s, int *i)
{
	if (s[(*i)] == '"')
	{
		while (s[(*i) + 1] != '"')
			(*i)++;
		(*i)++;
	}
}

void	skip_sq(char *s, int *i)
{
	if (s[(*i)] == '\'')
	{
		while (s[(*i) + 1] != '\'')
			(*i)++;
		(*i)++;
	}
}

bool	is_metachar(char c)
{
	if (c == '<' || c == '>' || c == ' ')
		return (true);
	else
		return (false);
}

bool	double_quotes(char *s, t_red **red, int *i)
{
	if (s[(*i)] == '"')
	{
		(*red)->left_over[(*red)->left_over_index] = -2;
		(*red)->left_over_index++;
		while (s[(*i) + 1] != '"')
		{
			(*i)++;
			(*red)->left_over[(*red)->left_over_index] = s[(*i)];
			(*red)->left_over_index++;
		}
		(*i)++;
		(*red)->left_over[(*red)->left_over_index] = -2;
		(*red)->left_over_index++;
		return (true);
	}
	else
		return (false);
}

bool	single_quotes(char *s, t_red **red, int *i)
{
	if (s[(*i)] == '\'')
	{
		(*red)->left_over[(*red)->left_over_index] = -1;
		(*red)->left_over_index++;
		while (s[(*i) + 1] != '\'')
		{
			(*i)++;
			(*red)->left_over[(*red)->left_over_index] = s[(*i)];
			(*red)->left_over_index++;
		}
		(*i)++;
		(*red)->left_over[(*red)->left_over_index] = -1;
		(*red)->left_over_index++;
		return (true);
	}
	else
		return (false);
}
