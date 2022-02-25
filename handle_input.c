
#include "minishell.h"

int	amount_redirections(char *current_process)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (current_process[i])
	{
		if (current_process[i] == '<')
		{
			if (current_process[i + 1] == '<')
				i++;
			count++;
		}
		else if (current_process[i] == '>')
		{
			if (current_process[i + 1] == '>')
				i++;
			count++;
		}
		i++;
	}
	printf("amount_redirections	%d\n", count);
	return (count);
}

int	char_compare(char *current_process, int *i)
{
	if (current_process[(*i)] == '<')
	{
		if (current_process[(*i) + 1] == '<')
		{
			(*i)++;
			return HEREDOC;

		}
		return INFILE;
	}
	else if (current_process[(*i)] == '>')
	{
		if (current_process[(*i) + 1] == '>')
		{
			(*i)++;
			return APPEND;
		}
		return TRUNCATE;
	}
	else
		return NOTHING;
}

bool	is_metachar(char c)
{
	if (c == '<' || c == '>' || c == ' ')
		return true;
	else
		return false;
}

char	*get_file(char *current_process, int *end)
{
	int	start;
	
	(*end)++;
	while (current_process[*end] == ' ')
		(*end)++;
	start = *end;
	while (current_process[*end] && !is_metachar(current_process[*end]))
		(*end)++;
	char *ret = ft_substr(current_process, start, (*end) - start);

	return (ret);
}

void	allocate_redirections(t_package **newNode, char *current_process)
{

	int		amount_red;

	amount_red = amount_redirections(current_process);
	(*newNode)->outfiles = (char **)malloc(sizeof(char *) * amount_red);
	(*newNode)->infiles = (char **)malloc(sizeof(char *) * amount_red);
	// mmuss hier plus eins hin, damit man das null setzt? wenn ja warum?
	//	maybe use ft_calloc
	(*newNode)->out_redirection = malloc(sizeof(int) * amount_red);
	(*newNode)->in_redirection = malloc(sizeof(int) * amount_red);

}

void	get_file_names(t_package **newNode, char *current_process, t_red **red)
{
	if ((*red)->operator == INFILE || (*red)->operator == HEREDOC)
	{
		(*newNode)->in_redirection[(*red)->iR] = (*red)->operator;
		(*newNode)->infiles[(*red)->iR] = get_file(current_process, &(*red)->i);
		(*red)->iR++;
	}
	else if ((*red)->operator == TRUNCATE || (*red)->operator == APPEND)
	{
		(*newNode)->out_redirection[(*red)->oR] = (*red)->operator;
		(*newNode)->outfiles[(*red)->oR] = get_file(current_process, &(*red)->i);
		(*red)->oR++;
	}
}

void	manage_red_files(t_package **newNode, char *current_process, t_red *red)
{
	// int		i = 0;
	red->i = 0;
	// int		operator;
	// int		remainder_index;

	red->left_over_index = 0;
	while (current_process[red->i])
	{
		red->operator = char_compare(current_process, &red->i);
		get_file_names(newNode, current_process, &red);
		// if (operator == INFILE || operator == HEREDOC)
		// {
		// 	(*newNode)->in_redirection[iR] = operator;
		// 	(*newNode)->infiles[iR] = get_file(current_process, &i);
		// 	iR++;
		// }
		// else if (operator == TRUNCATE || operator == APPEND)
		// {
		// 	(*newNode)->out_redirection[oR] = operator;
		// 	(*newNode)->outfiles[oR] = get_file(current_process, &i);
		// 	oR++;
		// }
		if (!is_metachar(current_process[red->i]))
		{
			red->left_over[red->left_over_index] = current_process[red->i];
			red->left_over_index++;
		}
		else
		{
			red->left_over[red->left_over_index] = ' ';
			red->left_over_index++;
		}
		if (current_process[red->i] != '<' && current_process[red->i] != '>')
			red->i++;
	}
}
char	*check_redirections(t_package **newNode, char *current_process)
{
	t_red	red;
	// int		iR = 0;
	// int		oR = 0;
	// char	*remainder;
		// int		operator;
		// int		i = 0;

	red.left_over = ft_calloc(ft_strlen(current_process) + 1, sizeof(char));
	allocate_redirections(newNode, current_process);
	manage_red_files(newNode, current_process, &red);
	// while (current_process[i])
	// {
	// 	operator = char_compare(current_process, &i);
	// 	if (operator == INFILE || operator == HEREDOC)
	// 	{
	// 		(*newNode)->in_redirection[iR] = operator;
	// 		(*newNode)->infiles[iR] = get_file(current_process, &i);
	// 		iR++;
	// 	}
	// 	else if (operator == TRUNCATE || operator == APPEND)
	// 	{
	// 		(*newNode)->out_redirection[oR] = operator;
	// 		(*newNode)->outfiles[oR] = get_file(current_process, &i);
	// 		oR++;
	// 	}
	// 	if (!is_metachar(current_process[i]))
	// 	{
	// 		remainder[remainder_index] = current_process[i];
	// 		remainder_index++;
	// 	}
	// 	else
	// 	{
	// 		remainder[remainder_index] = ' ';
	// 		remainder_index++;
	// 	}
	// 	if (current_process[i] != '<' && current_process[i] != '>')
	// 		i++;
	// }
	(*newNode)->in_redirection[red.iR] = NOTHING;
	(*newNode)->out_redirection[red.oR] = NOTHING;
	(*newNode)->infiles[red.iR] = NULL;
	(*newNode)->outfiles[red.oR] = NULL;
	return (red.left_over);
}


void	fill_package(t_package **newNode, char *current_process)
{
	char	*full_cmd;
	
	// printf("wheryu\n");
	full_cmd = ft_strtrim(check_redirections(newNode, current_process), " ");
	(*newNode)->cmd_args = special_split(full_cmd, ' ');
	(*newNode)->cmd = (*newNode)->cmd_args[0];
	
	for (int i = 0; (*newNode)->out_redirection[i] != 0; i++)
		printf("out_redirection[%d] = %d\n", i , (*newNode)->out_redirection[i]);
	for (int i = 0; (*newNode)->in_redirection[i] != 0; i++)
		printf("in_redirection[%d] = %d\n", i , (*newNode)->in_redirection[i]);
	for	(int i = 0; (*newNode)->infiles[i] != NULL; i++)
		printf("infiles[%d] = %s\n", i , (*newNode)->infiles[i]);
	for	(int i = 0; (*newNode)->outfiles[i] != NULL; i++)
		printf("outfiles[%d] = %s\n", i , (*newNode)->outfiles[i]);

	// freen - aber spater dann beim listen leeren
}

/*
andere Reihenfolge hier
um die cmd_args zu splitten mussen erst die spaces abgetrimmt werden
speichert cmd_args und cmd ab
*/

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
