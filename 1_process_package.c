#include "minishell.h"


void	fill_package(t_package **newNode, char *current_process)
{
	char	*full_cmd;

	
	// current_process = remove_quotes(&current_process);
	//hier muss noch ne function druber laufen, die alle quotes von den tokens entfernt
	//dann ist segfault maybe auch weg
	//in der die env abspeichern
	// 1 - quotes wegmachen
	// 2 - env expanden
	// 3 - neuen current_process.expanded anlegen
	//hier muss nach quotes geguckt werden, 
	full_cmd = ft_strtrim(get_command(newNode, current_process), " ");

	printf("FULLCMD		%s\n", full_cmd);
	(*newNode)->cmd_args = special_cmd_split(full_cmd, ' ');
	printf("(*newNode)->cmd_args		%p\n",(*newNode)->cmd_args);
	//special split verkackt iwie bei 
	(*newNode)->cmd = (*newNode)->cmd_args[0];

	//hier muss noch ne function druber laufen, die alle quotes von den tokens entfernt
	

	// freen - aber spater dann beim listen leeren
}


int	push_package(t_package **head, char *current_process)
{
	t_package *newNode;
	t_package *last;
	
	newNode = malloc(sizeof(t_package));
	if (newNode == NULL)
		return (1);
	ft_bzero(newNode, sizeof(t_package));
	fill_package(&newNode, current_process);
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


int process_packages(t_data *data)
{
	t_package	*current_package;
	int		i;

	i = 0;
	while (data->processes[i])
	{
		if (data->processes[i][0] != '\0')
			push_package(&data->head, data->processes[i]);
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
	// printf("hallo2\n");
	return (0);
}
/*
	process_packages pusht die packages & setzt den pipe bool fur alle packages
*/