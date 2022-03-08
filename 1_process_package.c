#include "minishell.h"

void	change_result(char **result, t_builtin *builtin)
{
	int		i;
	int		j;
	int		len;
	// int		fd[2];
	char	*tmp;


	i = 0;
	j = 0;
	tmp = NULL;
	while (result[i])
	{
		// if (result[i][j] == -1 && result[i][j] != '\0')
		// {
		// 	tmp = result[i];
		// 	result[i] = ft_strtrim(tmp, "\xFF");
		// 	//ist jetzt hier nicht nullterminiert etc
		// 	free(tmp);
		// }
		else if (result[i][j] == -2 && result[i][j] != '\0')
		{
			tmp = result[i];
			// if (pipe(fd) == -1)
			// 	write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			j++;
			while (result[i][j] != '\0')
			{
				//write in pipe[1] den char
				if (result[i][j] == '$' && result[i][j + 1] != ' ')
				{
					len = 0;
					j++;
					env_start = &result[i][j]
					while (result[i][j] != ' ')
						len++
						j++
					//extra function fur $string mit jeder env vergleichen
					//while
					ft_strncmp(env_start, builtin->env_list->content, len)
					
					//write in pipe[1]
				}
				//write normal cahr in pipe[1]
				j++;
			}
			// result[i] = muss auf pipe[0] zeigen;
			free(tmp);

		else
		{
			tmp = result[i];
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			j++;
			while (result[i][j] != '\0')
			{
				//write in pipe[1] den char
				if (result[i][j] == '$' && result[i][j + 1] != ' ')
				{
					//find right expandable
					//write in pipe[1]
					while (result[i][j] != ' ')
						j++
				}
				//write normal cahr in pipe[1]
				j++;
			}
			// result[i] = muss auf pipe[0] zeigen;
			free(tmp);
		}
		i++;
	}
	result[i] = NULL;
}


// 			lesen mt read, adnn hat mand ie lange und weiss wie grioss man neu mallocen muss 


//        ssize_t read(int fd, void *buf, size_t count);
// DESCRIPTION         top
//        read() attempts to read up to count bytes from file descriptor fd
//        into the buffer starting at buf.
// 	   ich kann da nicht result[i] als buf nehmen hat in split seine anzahl an chars bekommen
// 		}


void	fill_package(t_package **newNode, char *current_process, t_builtin *builtin)
{
	char	*full_cmd;

	//in der die env abspeichern
	// 1 - quotes wegmachen
	// 2 - env expanden
	// 3 - neuen current_process.expanded anlegen
	//hier muss nach quotes geguckt werden, 
	full_cmd = ft_strtrim(get_command(newNode, current_process), " ");
	(*newNode)->cmd_args = special_cmd_split(full_cmd, ' ');
	change_result((*newNode)->cmd_args, builtin);
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