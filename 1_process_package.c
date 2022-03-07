#include "minishell.h"

void	change_result(char **result)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (result[i])
	{
		if (result[i][j] == -1 && result[i][j] != '\0')
		{
			tmp = result[i];
			result[i] = ft_strtrim(tmp, "\xFF");
			//ist jetzt hier nicht nullterminiert etc
			free(tmp);
		}
		// else if (result[i][j] == -2 && result[i][j] != '\0')
		// {
		// 	tmp = result[i];
		// 	//pipe
		// 	//jeden char ausser Anfang/Ende quote in die pipe
		// 	//if $ dann expanden
		// 	//bis zum ende des $strings und weiter in die pipe
		// 	// result[i] = pipeinhalt;
//        ssize_t read(int fd, void *buf, size_t count);
// DESCRIPTION         top
//        read() attempts to read up to count bytes from file descriptor fd
//        into the buffer starting at buf.
// 			free(tmp);
		// }
		// else
		// //wenn keine quotes gesetzt
		// {
		// 	tmp = result[i];
		// 	//if $ dann expanden
		// 	//bis zum ende des $strings und weiter in die pipe
		// 	// result[i] = pipeinhalt;
		// 	free(tmp);
		// }

		i++;
	}
	result[i] = NULL;
}

void	fill_package(t_package **newNode, char *current_process)
{
	char	*full_cmd;

	//in der die env abspeichern
	// 1 - quotes wegmachen
	// 2 - env expanden
	// 3 - neuen current_process.expanded anlegen
	//hier muss nach quotes geguckt werden, 
	full_cmd = ft_strtrim(get_command(newNode, current_process), " ");
	(*newNode)->cmd_args = special_cmd_split(full_cmd, ' ');
	change_result((*newNode)->cmd_args);
	(*newNode)->cmd = (*newNode)->cmd_args[0];
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
	return (0);
}
/*
	process_packages pusht die packages & setzt den pipe bool fur alle packages
*/