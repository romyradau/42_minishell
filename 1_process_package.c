#include "minishell.h"

// void	change_result(char **result, t_builtin *builtin)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	int		fd[2];
// 	char	*tmp;
// 	char	*env_start;



// 	i = 0;
// 	j = 0;
// 	tmp = NULL;
// 	while (result[i])
// 	{
// 		if (result[i][j] == -1 && result[i][j] != '\0')
// 		{
// 			tmp = result[i];
// 			result[i] = ft_strtrim(tmp, "\xFF");
// 			// ist jetzt hier nicht nullterminiert etc
// 			free(tmp);
// 		}
// 		// if (result[i][j] == -2 && result[i][j] != '\0')
// 		// {
// 		// 	tmp = result[i];
// 		// 	// if (pipe(fd) == -1)
// 		// 	// 	write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
// 		// 	j++;
// 		// 	while (result[i][j] != '\0')
// 		// 	{
// 		// 		//write in pipe[1] den char
// 		// 		if (result[i][j] == '$' && result[i][j + 1] != ' ')
// 		// 		{
// 		// 			len = 0;
// 		// 			j++;
// 		// 			env_start = &result[i][j];
// 		// 			while (result[i][j] != ' ')
// 		// 			{
// 		// 				len++;
// 		// 				j++;

// 		// 			}
// 		// 			//extra function fur $string mit jeder env vergleichen
// 		// 			//while
// 		// 			while (builtin->env_list != NULL)
// 		// 			{
// 		// 				if (!ft_strncmp(builtin->env_list->content, env_start, len))
// 		// 					printf("content found : %s\n", builtin->env_list->content);
// 		// 				builtin->env_list = builtin->env_list->next;
// 		// 			}
					
// 		// 			//write in pipe[1]
// 		// 		}
// 		// 		//write normal cahr in pipe[1]
// 				j++;
// 			}
// 			// result[i] = muss auf pipe[0] zeigen;
// 			// free(tmp);
// 		}
// 		// else
// 		// {
// 		// 	tmp = result[i];
// 		// 	if (pipe(fd) == -1)
// 		// 		write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
// 		// 	j++;
// 		// 	while (result[i][j] != '\0')
// 		// 	{
// 		// 		//write in pipe[1] den char
// 		// 		if (result[i][j] == '$' && result[i][j + 1] != ' ')
// 		// 		{
// 		// 			//find right expandable
// 		// 			//write in pipe[1]
// 		// 			while (result[i][j] != ' ')
// 		// 				j++;
// 		// 		}
// 		// 		//write normal cahr in pipe[1]
// 		// 		j++;
// 		// 	}
// 		// 	// result[i] = muss auf pipe[0] zeigen;
// 		// 	free(tmp);
// 		}
// 		i++;
// 	}
// 	result[i] = NULL;
// }


// 			lesen mt read, adnn hat mand ie lange und weiss wie grioss man neu mallocen muss 


//        ssize_t read(int fd, void *buf, size_t count);
// DESCRIPTION         top
//        read() attempts to read up to count bytes from file descriptor fd
//        into the buffer starting at buf.
// 	   ich kann da nicht result[i] als buf nehmen hat in split seine anzahl an chars bekommen
// 		}

char	*simple_expand(const char *s, int c)
{
	char			ch;
	char			*newS;
	unsigned int	cnt;//fur bis !alnum

	cnt = 0;
	ch = (char) c;
	newS = (char *)s;
	//hier while bis cnt auff !alnum ist
	
	while (*newS != ch)
	{
		if (*newS == '\0')
			return (0);
		newS++;
	}
	if (*newS+1 != ' ')
		return (newS+1);
		//hier strncmp
		//in die pipe scchreiben
		//dann s[cnt] in die pipe schreiben
	return (NULL);
}

int complex_expand(char **s,int *fd, int *count, t_envlist *tmp_list)
{

	char			*newS;
	int				cnt;
	int				tmp_i;
	char			*expand_content;

	newS = (char *)(*s);
	cnt = 0;
	tmp_i = 0;
	while (*newS != '$')
	{	
		if (*newS == '\0')
			return (0);
		newS++;
		tmp_i++;
	}
	printf("d: %d\n", *(newS + 1));
	if (*(newS+1) != ' ' && *(newS + 1) != 0)
		newS++;
	else
	{
		return (0);
	}
	while(newS[cnt] != '\0' && (ft_isalnum(newS[cnt]) || newS[cnt] == '_'))
		cnt++;

	while (tmp_list != NULL)
	{
		if (!ft_strncmp(tmp_list->content, newS, cnt))//cnt//vlt problem weil er immer dass fd closed?
		{
			printf("newS: %c\n", *newS);
			expand_content = ft_strdup(simple_expand(tmp_list->content, '='));
			if (!expand_content)
				return (0);
			//schau ob new es was noch hat wis z.b ...	
			(*count) += ft_strlen(expand_content);
			free((*s));
			ft_putstr_fd(expand_content,fd[1]);
			printf("s = %s\n", (*s));
			while (newS[cnt] != '\0')
			{
				write(fd[1], &newS[cnt], 1);
				cnt++;
				(*count)++;
			}
			(*s) = ft_strcalloc((*count));
			if (!(*s))
				return (0);
			if (read(fd[0], (*s), (*count)) == -1)
				return (0);
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		tmp_list = tmp_list->next;
	}
	while (newS[cnt] != '\0')
	{
		printf("nesw[cnt] 		%c\n", newS[cnt]);
		write(fd[1], &newS[cnt], 1);
		cnt++;
		(*count)++;
	}
	(*s) = ft_strcalloc((*count));
	if (!(*s))
		return (0);
	if (read(fd[0], (*s), (*count)) == -1)
		return (0);
	close(fd[0]);
	close(fd[1]);
	return (1);
}



int expand_result_standart(char **res, t_builtin *builtin)
{
	t_envlist	*tmp_list;
	char		*env_start;
	char		*expand_content;
	char		*tmp;
	int			fd[2];
	int			i;
	int			j;
	int			cnt;
	int			count;

	tmp_list = builtin->env_list;
	i = 0;
	j = 0;
	cnt = 0;
	count = 0;
	//*find "$" singe
	while (res[i] != NULL)
	{
		if (res[i][j] == -1 && res[i][j] != '\0')
 		{
 			tmp = res[i];
 			res[i] = ft_strtrim(tmp, "\xFF");
 			// ist jetzt hier nicht nullterminiert etc
 			free(tmp);
 		}
		else if (ft_strchr(res[i], '$') && res[i][j] == -2)
		{	
			tmp = res[i];
 			res[i] = ft_strtrim(tmp, "\xFE");
 			// ist jetzt hier nicht nullterminiert etc
 			free(tmp);
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			if (res[i][j] == '$' && res[i][j + 1] == '\0')
				return (1);
			while (res[i][j] != '\0' && res[i][j] != '$')
			{
				write(fd[1], &res[i][j], 1);
				j++;
				count++;
				if (res[i][j] == '$')
					break;
			}
			// env_start = ft_strdup(complex_expand(&res[i], fd , &count, tmp_list));
			// if (!env_start)
			// 	return (0);
			while (tmp_list != NULL)
			{
				if (!ft_strncmp(tmp_list->content, env_start, cnt))
				{
						expand_content = ft_strdup(simple_expand(tmp_list->content, '='));
						if (!expand_content)
							return (0);
						count += ft_strlen(expand_content);
						free(res[i]);
						ft_putstr_fd(expand_content,fd[1]);
						res[i] = ft_strcalloc(count);
						if (!res[i])
							return (0);
						if (read(fd[0], res[i], count) == -1)
							return (0);
						close(fd[0]);
						close(fd[1]);
						return (1);
				}
				tmp_list = tmp_list->next;
			}
		}
		else if (ft_strchr(res[i], '$'))
		{
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
				//hier noch die dollar dollar billion scheisse einfugen
			if (res[i][j] == '$' && res[i][j + 1] == '\0')
				return (1);
			while (res[i][j] != '\0' && res[i][j] != '$')
			{
				write(fd[1], &res[i][j], 1);
				j++;
				count++;
				if (res[i][j] == '$')
					break;
			}
			//part der alles vr $ in pipe schreibt
			// env_start = ft_strdup(complex_expand(&res[i], '$', &cnt, fd));
			// if (!env_start)
			// 	return (0);
			if (complex_expand(&res[i], fd, &count, tmp_list) == 0)
			{
				if (res[i][j] == '$' && (res[i][j + 1] == '\0'))
				{
					printf("Res[i][j]: %c\n", res[i][j]);
					write(fd[1], &res[i][j], 1);
					count++;
					j++;
				}
				tmp = res[i];
			// free(res[i]);
				res[i] = ft_strcalloc(count);
				if (read(fd[0], res[i], count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				res[i][j] = '\0';
 				// ist jetzt hier nicht nullterminiert etc
 				free(tmp);
			}
			printf("res[i]: %s\n", res[i]);
		}
		i++;
	}
	return (0);
}

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
	// change_result((*newNode)->cmd_args, builtin);
	expand_result_standart((*newNode)->cmd_args, builtin);
	printf("fill_package: cmd: %s\n", (*newNode)->cmd_args[0]);
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