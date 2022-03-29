#include "../../minishell.h"

t_envlist	*creat_node(const char *src)
{
	t_envlist	*tmp;

	tmp = (t_envlist *)malloc(sizeof(t_envlist));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strdup(src);
	if (!tmp->content)
		return (NULL);
	if (!ft_strchr(src, '='))
		tmp->hiden = true;
	else
		tmp->hiden = false;
	tmp->next = NULL;
	return (tmp);
}

int	add_node(t_envlist **head, const char *src)
{
	t_envlist	*newnode;

	newnode = creat_node(src);
	if (!newnode)
		return (0);
	newnode->next = (*head);
	newnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = newnode;
	(*head) = newnode;
	return (1);
}

int	reverse_envlist(t_envlist **list)
{
	t_envlist	*tmp;
	t_envlist	*current;

	tmp = NULL;
	if (!(*list))
		return (0);
	current = *list;
	while (current != NULL)
	{
		tmp = current->prev;
		current->prev = current->next;
		current->next = tmp;
		current = current->prev;
	}
	if (tmp != NULL)
		*list = tmp->prev;
	return (1);
}

int	set_envlist(t_data *data, t_envlist **list)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (!add_node(list, data->env[i]))
			return (0);
		i++;
	}
	if (!reverse_envlist(list))
		return (0);
	return (1);
}

int	if_ans_wrong(char **str, char **anws)
{
	if (!(*anws))
	{
		(*anws) = ft_strtrim((*str), ft_strchr((*str), '='));
		if (!simple_check((*anws)))
		{
			if ((*anws[0]) == '_')
			{
				free((*anws));
				return (1);
			}
			free ((*anws));
			printf("export: %s: not a valid identifier\n", (*str));
			g_exit_stat = 1;
			return (1);
		}
		free((*anws));
		return (1);
	}
	return (0);
}
