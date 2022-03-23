
#include "minishell.h"

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
		if (current_process[i] == '<')
		{
			if (current_process[i + 1] == '<')
				i++;
			if (current_process[i + 1] == '<' || current_process[i + 1] == '>')
				return (-1);
			count++;
		}
		else if (current_process[i] == '>')
		{
			if (current_process[i + 1] == '>')
				i++;
			if (current_process[i + 1] == '>' || current_process[i + 1] == '<')
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	allocate_redirections(t_package **newNode, char *current_process)
{

	int		amount_red;

	amount_red = amount_redirections(current_process);
	(*newNode)->outfiles = ft_calloc(amount_red + 1, sizeof(char *));
	(*newNode)->infiles = ft_calloc(amount_red + 1, sizeof(char *));
	// muss hier plus eins hin, damit man das null setzt? wenn ja warum?
	// vlt spater probleme beim zugreifen auf files wo nichts allociert wurde!
	// maybe use ft_calloc
	(*newNode)->out_redirection = ft_calloc(amount_red + 1, sizeof(int));
	(*newNode)->in_redirection = ft_calloc(amount_red + 1, sizeof(int));
	return (amount_red);
}

/*
allocate_redirections = findet raus wie viele reds/files es gibt und allocated deren space
*/