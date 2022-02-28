#include "minishell.h"

char	*store_filename(char *current_process, int *end)
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


void	store_redirection(t_package **newNode, char *current_process, t_red **red)
{
	if ((*red)->operator == INFILE || (*red)->operator == HEREDOC)
	{
		(*newNode)->in_redirection[(*red)->iR] = (*red)->operator;
		(*newNode)->infiles[(*red)->iR] = store_filename(current_process, &(*red)->i);
		(*red)->iR++;
	}
	else if ((*red)->operator == TRUNCATE || (*red)->operator == APPEND)
	{
		(*newNode)->out_redirection[(*red)->oR] = (*red)->operator;
		(*newNode)->outfiles[(*red)->oR] = store_filename(current_process, &(*red)->i);
		(*red)->oR++;
	}
}

void	manage_red_files(t_package **newNode, char *current_process, t_red *red)
{
	red->i = 0;
	red->left_over_index = 0;
	while (current_process[red->i])
	{
		red->operator = char_compare(current_process, &red->i);
		store_redirection(newNode, current_process, &red);
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

char	*get_command(t_package **newNode, char *current_process)
{
	t_red	red;

	ft_bzero(&red, sizeof(t_red));
	red.left_over = ft_calloc(ft_strlen(current_process) + 1, sizeof(char));
	allocate_redirections(newNode, current_process);
	manage_red_files(newNode, current_process, &red);
	(*newNode)->in_redirection[red.iR] = NOTHING;
	(*newNode)->out_redirection[red.oR] = NOTHING;
	(*newNode)->infiles[red.iR] = NULL;
	(*newNode)->outfiles[red.oR] = NULL;
	return (red.left_over);
}


void	fill_package(t_package **newNode, char *current_process)
{
	char	*full_cmd;

	//hier muss noch ne function druber laufen, die alle quotes von den tokens entfernt
	//dann ist segfault maybe auch weg
	//in der die env abspeichern
	// 1 - quotes wegmachen
	// 2 - env expanden
	// 3 - neuen current_process.expanded anlegen
	full_cmd = ft_strtrim(get_command(newNode, current_process), " ");
	(*newNode)->cmd_args = special_split(full_cmd, ' ');
	(*newNode)->cmd = (*newNode)->cmd_args[0];
	//hier muss noch ne function druber laufen, die alle quotes von den tokens entfernt
	

	// freen - aber spater dann beim listen leeren
}

/*
fill_package = speichert den command & seine cmd_args
get_command = macht platz fur den command und die reds und die files
manage_red_files = sucht nach der aktuellen red schickt weiter zu
store_redirection = speichert die red an
store_filename = speichert den dazugehörigen filename ab
*/

