/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:45:04 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 23:04:51 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_builtin *builtin)
{
	t_envlist	*tmp;

	tmp = builtin->env_list;
	if (builtin->env_list == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (tmp->next != NULL && tmp->hiden == true)
			tmp = tmp->next;
		else
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_equel_check(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if ((int)ft_strlen(str) == i || i == 0)
		return (0);
	return (i);
}

int	ft_unset(t_envlist **list, const char *arg, char ***env_cpy)
{
	t_envlist	*tmp;
	int			len;

	tmp = *list;
	len = 0;
	if (arg == NULL)
		return (g_exit_stat = 1);
	while (tmp->next != NULL)
	{
		if (!ft_strncmp((const char *)tmp->content, arg,
				ft_equel_check(tmp->content, '='))
			&& (ft_equel_check(tmp->content, '=') == (int)ft_strlen(arg)))
		{
			del_env_node(list, len, tmp);
			if (update_new_env(env_cpy, (*list)))
				return (1);
			return (0);
		}
		tmp = tmp->next;
		len++;
	}
	if (dlasnode(list, arg, env_cpy, tmp))
		return (g_exit_stat = 0);
	return (0);
}
