
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

void	allocate_redirections(t_package **newNode, char *current_process)
{

	int		amount_red;

	amount_red = amount_redirections(current_process);
	printf(" amount_red	%d\n", amount_red);
	(*newNode)->outfiles = malloc(sizeof(char *) * amount_red);
	(*newNode)->infiles = malloc(sizeof(char *) * amount_red);
	// muss hier plus eins hin, damit man das null setzt? wenn ja warum?
	// vlt spater probleme beim zugreifen auf files wo nichts allociert wurde!
	// maybe use ft_calloc
	(*newNode)->out_redirection = malloc(sizeof(int) * amount_red);
	(*newNode)->in_redirection = malloc(sizeof(int) * amount_red);
}

/*
allocate_redirections = findet raus wie viele reds/files es gibt und allocated deren space
*/