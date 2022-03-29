/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_get_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:16:25 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 19:16:27 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename(char *current, t_red **red)
{
	int		start;
	char	*filename;

	(*red)->i++;
	while (current[(*red)->i] == ' ')
		(*red)->i++;
	start = (*red)->i;
	while (current[(*red)->i] && !is_metachar(current[(*red)->i])
		&& current[(*red)->i] != '\0')
		(*red)->i++;
	filename = ft_substr(current, start, (*red)->i - start);
	return (filename);
}

int	store_redirection(t_package **newNode, char *current, t_red **red)
{
	if ((*red)->operator == INFILE || (*red)->operator == HEREDOC)
	{
		(*newNode)->in_redirection[(*red)->in] = (*red)->operator;
		(*newNode)->infiles[(*red)->in] = filename(current, red);
		if ((*newNode)->infiles[(*red)->in] == NULL)
			return (0);
		(*red)->in++;
	}
	else if ((*red)->operator == TRUNCATE || (*red)->operator == APPEND)
	{
		(*newNode)->out_redirection[(*red)->out] = (*red)->operator;
		(*newNode)->outfiles[(*red)->out] = filename(current, red);
		if ((*newNode)->outfiles[(*red)->out] == NULL)
			return (0);
		(*red)->out++;
	}
	return (1);
}

int	in_or_out(char *current, int *i)
{
	if (current[(*i)] == '<')
	{
		if (current[(*i) + 1] == '<')
		{
			(*i)++;
			if (current[(*i) + 1] == '<' || current[(*i) + 1] == '>')
				return (-1);
			return (HEREDOC);
		}
		return (INFILE);
	}
	else if (current[(*i)] == '>')
	{
		if (current[(*i) + 1] == '>')
		{
			(*i)++;
			if (current[(*i) + 1] == '>' || current[(*i) + 1] == '<')
				return (-1);
			return (APPEND);
		}
		return (TRUNCATE);
	}
	else
		return (NOTHING);
}

int	manage_red_files(t_package **newNode, char *current, t_red *red)
{
	red->i = 0;
	red->left_over_index = 0;
	while (current[red->i] != '\0')
	{
		red->operator = char_compare(current, &red, &red->i);
		if (store_redirection(newNode, current, &red) == 0)
			return (0);
		if (!is_metachar(current[red->i]) && current[red->i] != '"'
			&& current[red->i] != '\'')
		{
			red->left_over[red->left_over_index] = current[red->i];
			red->left_over_index++;
		}
		else if (current[red->i] != '"' && current[red->i] != '\'')
		{
			red->left_over[red->left_over_index] = ' ';
			red->left_over_index++;
		}
		if (current[red->i] == '\0')
			break ;
		if (current[red->i] != '<' && current[red->i] != '>'
			&& current[red->i] != '"' && current[red->i] != '\'')
			red->i++;
	}
	return (1);
}

char	*get_command(t_package **newNode, char *current)
{
	t_red	red;

	ft_bzero(&red, sizeof(t_red));
	red.left_over = ft_calloc(ft_strlen(current) + 1, sizeof(char));
	if (allocate_redirections(newNode, current) == -1)
	{
		free(red.left_over);
		return (NULL);
	}
	if (manage_red_files(newNode, current, &red) == 0)
	{
		free(red.left_over);
		return (NULL);
	}
	(*newNode)->in_redirection[red.in] = NOTHING;
	(*newNode)->out_redirection[red.out] = NOTHING;
	(*newNode)->infiles[red.in] = NULL;
	(*newNode)->outfiles[red.out] = NULL;
	return (red.left_over);
}
