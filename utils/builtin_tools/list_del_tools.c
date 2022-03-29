
#include "../../minishell.h"

int	del_env_node(t_envlist **list, int len, t_envlist *tmp)
{
	if (len == 0)
	{
		*list = (*list)->next;
		ft_bzero(tmp->content, ft_strlen(tmp->content));
		free(tmp);
		tmp = NULL;
		if ((*list) != NULL)
			(*list)->prev = NULL;
		return (1);
	}
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	ft_bzero(tmp->content, ft_strlen(tmp->content));
	free(tmp);
	tmp = NULL;
	return (1);
}

int	del_lasnode(t_envlist **l, const char *arg, char ***env_cpy, t_envlist *tmp)
{
	int	len_cont;
	int	len_arg;

	len_cont = 0;
	len_arg = 0;
	if (tmp->next == NULL)
	{
		len_cont = ft_equel_check(tmp->content, '=');
		len_arg = (int)ft_strlen(arg);
		if (!ft_strncmp((const char *)tmp->content, arg, len_cont)
			&& (len_cont == len_arg))
		{
			tmp->prev->next = NULL;
			free(tmp);
			if (update_new_env(env_cpy, (*l)))
				return (1);
			return (0);
		}
	}
	return (0);
}
