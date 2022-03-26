
#include "../minishell.h"

static t_envlist *creat_node(const char *src)
{
	t_envlist *tmp;

	tmp = (t_envlist *)malloc(sizeof(t_envlist));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strdup(src);
	if (!ft_strchr(src, '='))
		tmp->hiden = true;
	else
		tmp->hiden = false;
	tmp->next = NULL;
	return (tmp);
}

int add_node(t_envlist **head, const char *src)
{
	t_envlist *newnode;
	
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

int reverse_envlist(t_envlist **list)
{
	t_envlist *tmp;
	t_envlist *current;

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

int set_envlist(t_data *data, t_envlist **list)
{
	int i;
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

int print_env(t_builtin *builtin)
{
	t_envlist *tmp;

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

int ft_equel_check(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break;
		i++;
	}
	if ((int)ft_strlen(str) == i || i == 0)
		return (0);
	return (i);
}

int del_env_node(t_envlist **list, int len, t_envlist *tmp)
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

int	ft_unset(t_envlist **list, const char *arg)
{
	printf("UNSET runs\n");
	t_envlist	*tmp;
	// t_envlist	*tmp2;
	int len;
	int len_cont;
	int len_arg;

	tmp = *list;
	len = 0;
	len_cont = 0;
	len_arg = 0;
	if (arg == NULL)
	{
		g_exit_stat = 1;
		return (0);
	}
	while (tmp->next != NULL)
	{
		len_cont = ft_equel_check(tmp->content, '=');
		len_arg = (int)ft_strlen(arg);
		if (!ft_strncmp((const char *)tmp->content, arg, len_cont) && (len_cont == len_arg))
		{
			del_env_node(list, len, tmp);
			return (1);
		}
		tmp = tmp->next;
		len++;
	}
	if (tmp->next == NULL)
	{
		len_cont = ft_equel_check(tmp->content, '=');
		len_arg = (int)ft_strlen(arg);
		if (!ft_strncmp((const char *)tmp->content, arg, len_cont) && (len_cont == len_arg))
		{
			tmp->prev->next = NULL;
			free(tmp);
			return(1);
		}
	}
	return (0);
}