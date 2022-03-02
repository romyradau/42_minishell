
#include "minishell.h"

// int	amount_redirections(char *s)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '<' && s[i - 1] != '"')
// 		//warum segfaultet das nicht bei <infile ??
// 		{
// 			if (s[i + 1] == '<' && s[i - 2] != '"')
// 				i++;
// 			count++;
// 		}
// 		else if (s[i] == '>' && s[i - 1] != '"')
// 		{
// 			if (s[i + 1] == '>' && s[i - 1] != '"')
// 				i++;
// 			count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }
void	skip_dq(char *s, int *i)
{
	if (s[(*i)] == '"')
	{
		while (s[(*i) + 1] != '"')
			(*i)++;
		(*i)++;
	}
}

void	skip_sq(char *s, int *i)
{
	if (s[(*i)] == '\'')
	{
		while (s[(*i) + 1] != '\'')
			(*i)++;
		(*i)++;
	}
}

int	amount_redirections(char *current_process)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (current_process[i])
	{
		skip_dq(current_process, &i);
		skip_sq(current_process, &i);
		// if (current_process[i] == '"')
		// {
		// 	while (current_process[i + 1] != '"')
		// 		i++;
		// 	i++;
		// }
		// if (current_process[i] == '\'')
		// {
		// 	while (current_process[i + 1] != '\'')
		// 		i++;
		// 	i++;
		// }
		//skip alles bis zur nachsten quote
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
//real punkte merken und die direkt in die struct speichern
//vlt das gleiche auf char _compare anweden
		// if (current_process[i] == '"')
		// {
		// 	while (current_process[i + 1] != '"')
		// 		i++;
		// 	i++;
		// }
		// if (current_process[i] == '\'')
		// {
		// 	while (current_process[i + 1] != '\'')
		// 		i++;
		// 	i++;
		// }
//die auslagern und auch in char_compare rein


bool	double_quotes(char *s, t_red **red, int *i)
{
	if (s[(*i)] == '"')
	{
		while (s[(*i) + 1] != '"')
		{
			(*i)++;
			(*red)->left_over[(*red)->left_over_index] = s[(*i)];
			(*red)->left_over_index++;
		}
		(*i)++;
		return true;
	}
	else
		return false;
}

bool	single_quotes(char *s, t_red **red, int *i)
{
	if (s[(*i)] == '\'')
	{
		// (*red)->left_over[(*red)->left_over_index] = '*';
			// (*red)->left_over_index++;

		while (s[(*i) + 1] != '\'')
		{
			(*i)++;
			// printf("character	%c\n", s[(*i)]);
			(*red)->left_over[(*red)->left_over_index] = s[(*i)];
			(*red)->left_over_index++;
		}
		(*i)++;
		// printf("(*red)->left_over[(*red)->left_over_index]	%d\n", (*red)->left_over_index);
		// (*red)->left_over[(*red)->left_over_index] = '*';
		// //warum schreibt der den letzten assterix da nicht hin ?!
		return true;
	}
	else
		return false;
}
//left over index bool implementieren
//auf den stellen der quotes ander zeichen rein hard coden und die dann in der split beachten s.o.

int	char_compare(char *current_process, t_red **red, int *i)
{
	if (double_quotes(current_process, red, i))
		(*i)++;
	if (single_quotes(current_process, red, i))
		(*i)++;
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