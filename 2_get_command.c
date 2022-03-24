#include "minishell.h"

char	*filename(char *current, int *end)
{
	int		start;
	char	*filename;

	(*end)++;
	while (current[*end] == ' ')
		(*end)++;
	start = *end;
	while (current[*end] && !is_metachar(current[*end])
		&& current[*end] != '\0')
		(*end)++;
	filename = ft_substr(current, start, (*end) - start);
	printf("filename	%s\n", filename);
	return (filename);
}

int	store_redirection(t_package **newNode, char *current, t_red **red)
{
	if ((*red)->operator == INFILE || (*red)->operator == HEREDOC)
	{
		(*newNode)->in_redirection[(*red)->iR] = (*red)->operator;
		(*newNode)->infiles[(*red)->iR] = filename(current, &(*red)->i);
		if ((*newNode)->infiles[(*red)->iR] == NULL)
			return (0);
		(*red)->iR++;
	}
	else if ((*red)->operator == TRUNCATE || (*red)->operator == APPEND)
	{
		(*newNode)->out_redirection[(*red)->oR] = (*red)->operator;
		(*newNode)->outfiles[(*red)->oR] = filename(current, &(*red)->i);
		if ((*newNode)->outfiles[(*red)->oR] == NULL)
			return (0);
		(*red)->oR++;
	}
	return (1);
}

int		in_or_out(char *current, int *i)
{
	if (current[(*i)] == '<')
	{
		if (current[(*i) + 1] == '<')
		{
			(*i)++;
			if (current[(*i) + 1] == '<' || current[(*i) + 1] == '>')
				return (-1);
			return (HEREDOC);
		}
		return (INFILE);
	}
	else if (current[(*i)] == '>')
	{
		if (current[(*i) + 1] == '>')
		{
			(*i)++;
			if (current[(*i) + 1] == '>' || current[(*i) + 1] == '<')
				return (-1);
			return (APPEND);
		}
		return (TRUNCATE);
	}
	else
		return (NOTHING);
}

int	char_compare(char *current, t_red **red, int *i)
{
	if (double_quotes(current, red, i))
		(*i)++;
	if (single_quotes(current, red, i))
		(*i)++;
	return (in_or_out(current, i));
}

int	manage_red_files(t_package **newNode, char *current, t_red *red)
{
	red->i = 0;
	red->left_over_index = 0;
	while (current[red->i])
	{
		red->operator = char_compare(current, &red, &red->i);
		if (store_redirection(newNode, current, &red) == 0)
			return (0);
		if (!is_metachar(current[red->i]) && current[red->i] != '"'
			&& current[red->i] != '\'')
		{
			red->left_over[red->left_over_index] = current[red->i];
			red->left_over_index++;
		}
		else if (current[red->i] != '"' && current[red->i] != '\'')
		{
			red->left_over[red->left_over_index] = ' ';
			red->left_over_index++;
		}
		if (current[red->i] != '<' && current[red->i] != '>'
			&& current[red->i] != '"' && current[red->i] != '\'')
			red->i++;
	}
	return (1);
}
/*
fill_package = speichert den command & seine cmd_args
get_command = macht platz fur den command und die reds und die files
manage_red_files = sucht nach der aktuellen red schickt weiter zu
store_redirection = speichert die red an
store_filename = speichert den dazugehörigen filename ab
*/
