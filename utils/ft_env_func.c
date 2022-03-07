
#include "../minishell.h"

static t_envlist *creat_node(const char *src)
{
	t_envlist *tmp;

	tmp = (t_envlist *)malloc(sizeof(t_envlist));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strdup(src);
	tmp->next = NULL;
	return (tmp);
}

static int add_node(t_envlist **head, const char *src)
{
	t_envlist *newnode;
	
	newnode = creat_node(src);
	if (!newnode)
		return (0);
	// if (*head == NULL)
	// {
	// 	*head = newnode;
	// 	(*head)->next = NULL;
	// 	return (0);
	// }
	newnode->next = (*head);
	newnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = newnode;
	(*head) = newnode;
	// while (last->next != NULL)
	// 	last = last->next;
	// last->next = newnode;
	// newnode->next = NULL;
	return (0);

}

int set_envlist(t_data *data, t_envlist **list)
{
	int i;
	i = 0;
	while (data->env[i] != NULL)
	{
		if (add_node(list, data->env[i]))
			return (0);
		i++;
	}
	return (1);

}

int print_env(t_builtin *builtin)
{
	printf("print env is called\n");
	t_envlist *tmp;

	tmp = builtin->env_list;
	if (builtin->env_list == NULL)
	{
		printf("THis sheeet is\n");
		return (1);
	}
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (0);
}


int	ft_unset(t_envlist **list, const char *arg)
{
	printf("UNSET runs\n");
	t_envlist	*tmp;
	// t_envlist	*tmp2;
	
	tmp = *list;
	while (tmp->next != NULL)
	{
		if (!ft_strncmp((const char *)tmp->content, arg, ft_strlen(arg)))
		{
			// tmp2 = tmp;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			// free(tmp);
			ft_bzero(tmp->content, ft_strlen(tmp->content));
			free(tmp);
			tmp = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * void deleteNode(struct Node** head_ref, int key)
{
    // Store head node
    struct Node *temp = *head_ref, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    free(temp); // Free memory
}
*/
// int ft_export();

/**
USER - The current logged in user.
HOME - The home directory of the current user.
EDITOR - The default file editor to be used. This is the editor that will be used when you type edit in your terminal.
SHELL - The path of the current user’s shell, such as bash or zsh.
LOGNAME - The name of the current user.
PATH - A list of directories to be searched when executing commands. When you run a command the system will search those directories in this order and use the first found executable.
LANG - The current locales settings.
TERM - The current terminal emulation.
MAIL - Location of where the current user’s mail is stored.
*/