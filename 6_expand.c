/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:51:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 20:04:09 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*simple_expand(const char *s, int c)
{
	char			ch;
	char			*str;
	unsigned int	cnt;

	cnt = 0;
	ch = (char) c;
	str = (char *)s;
	while (*str != ch)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	if (*str + 1 != ' ')
		return (str + 1);
	return (NULL);
}

int	do_the_expansion(t_envlist *tmp_list, t_exp *exp, int end_of_var)
{
	char	*expand_content;

	expand_content = ft_strdup(simple_expand(tmp_list->content, '='));
	if (!expand_content)
		return (1);
	exp->len += ft_strlen(expand_content);
	write(exp->fd[1], expand_content, ft_strlen(expand_content));
	free(expand_content);
	(void)end_of_var;
	return (0);
}

int	find_end_of_var(t_exp *exp, char *str, int *count, int *end_of_var)
{
	if (str[exp->i] == -1 || str[exp->i] == -2)
		return (1);

	if (str[exp->i] == '?' && str[exp->i + 1] == '\0')
	{
		get_exit_status(g_exit_stat, exp->fd[1], exp);
		return (1);
	}
	(*count) = 0;
	(*end_of_var) = exp->i;
	while (str[(*end_of_var)] != '\0'
		&& (ft_isalnum(str[(*end_of_var)]) || str[(*end_of_var)] == '_'))
	{
		(*end_of_var)++;
		(*count)++;
	}
	return (0);
}

int	complex_expand(char *str, t_exp *exp, t_envlist *list)
{
	int		end_of_var;
	int		count;

	if (str[exp->i + 1] != ' ')
		exp->i++;
	else
		return (0);
	if (find_end_of_var(exp, str, &count, &end_of_var) == 1)
		return (1);

	while (list != NULL && count)
	{
		if (!ft_strncmp(list->content, &str[exp->i], xyz(list->content, '='))
			&& (xyz(list->content, '=') == count))
		{
			if (do_the_expansion(list, exp, end_of_var))
				return (0);
		}
		list = list->next;
	}
	exp->i += count;
	if (!count)
		write(1, "$", 1);
	return (1);
}


int	expand_function(char *str, t_exp *exp, t_builtin *builtin)
{
	t_envlist	*tmp_list;

	tmp_list = builtin->env_list;
	if (str[exp->i] == '$' && str[exp->i + 1] == '\0')
		return (1);
	if (complex_expand(str, exp, tmp_list) == 0)
	{
		exp->i++;
		return (1);
	}
	return (0);
}
