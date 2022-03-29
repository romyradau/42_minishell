/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:22 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/30 00:04:08 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	del_env_node(t_envlist **list, int len, t_envlist *tmp)
{
	if (len == 0)
	{
		*list = (*list)->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
		if ((*list) != NULL)
			(*list)->prev = NULL;
		return (1);
	}
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	free(tmp->content);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	dlasnode(t_envlist **l, const char *a, char ***env_cpy, t_envlist *t)
{
	int	len_cont;
	int	len_arg;

	len_cont = 0;
	len_arg = 0;
	if (t->next == NULL)
	{
		len_cont = ft_equel_check(t->content, '=');
		len_arg = (int)ft_strlen(a);
		if (!ft_strncmp((const char *)t->content, a, len_cont)
			&& (len_cont == len_arg))
		{
			t->prev->next = NULL;
			free(t);
			if (update_new_env(env_cpy, (*l)))
				return (1);
			return (0);
		}
	}
	return (0);
}
