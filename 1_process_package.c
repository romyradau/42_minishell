#include "minishell.h"

void	fill_package(t_package **newNode, char *current_process, t_builtin *builtin)
{
	char	*full_cmd;
	full_cmd = ft_strtrim(get_command(newNode, current_process), " ");
	(*newNode)->cmd_args = special_cmd_split(full_cmd, ' ');
	clean_expand((*newNode)->cmd_args, builtin);
	(*newNode)->cmd = (*newNode)->cmd_args[0];
	// freen - aber spater dann beim listen leeren
}


int	push_package(t_package **head, char *current_process, t_builtin *builtin)
{
	t_package *newNode;
	t_package *last;
	
	newNode = malloc(sizeof(t_package));
	if (newNode == NULL)
		return (1);
	ft_bzero(newNode, sizeof(t_package));
	fill_package(&newNode, current_process, builtin);
	last = *head;
	if (*head == NULL)
	{
		*head = newNode;
		(*head)->next = NULL;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	newNode->next = NULL;
	return (0);
}
//kreiert neue node
//neue node next ist NULL
//versteh des noch nicht ganz....


int process_packages(t_data *data, t_builtin *builtin)
{
	t_package	*current_package;
	int		i;

	i = 0;
	while (data->processes[i])
	{
		if (data->processes[i][0] != '\0')
			push_package(&data->head, data->processes[i], builtin);
		//braucht man != '\0' noch??? 
		//nicht wirklich but i keep it though
		//glaube das war weil's eins zu viel gab mit ner \0 drin
		current_package = data->head;
		if (data->processes[i] != NULL)
		{
			while (current_package->next)
			{
				current_package->pipe = true;
				current_package = current_package->next;
			}
		}
		i++;
	}
	return (0);
}
/*
	process_packages pusht die packages & setzt den pipe bool fur alle packages
*/