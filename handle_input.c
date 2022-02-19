/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:59 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/20 00:40:55 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	print_package(t_package *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("cmd:	%s\n", head->cmd);
		while (head->cmd_args && head->cmd_args[0])
		{
			printf("cmd_args:	%s\n", head->cmd_args[i]);
			head->cmd_args++;
		}
		printf("pipe:	%d\n", head->pipe);
		head = head->next;
	}
}

void	print2Darray(char **split)
{
	int	i;

	i = 0;
	printf("-------- pipe_package start --------\n");
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	printf("-------- pipe_package end --------\n\n");
}

int	char_compare(char *current_process, int *i)
{
	if (current_process[(*i)] == '<')
	{
		if (current_process[(*i) + 1] == '<')
		{
			(*i)++;
			// printf("input<<: 	%s\n", input);
			//function die "des danach" als package->redirection speichert
			//muss aber noch als char * abgespeichert werden
			return HEREDOC;

		}
		// printf("input<: 	%s\n", input);
		//function die "des danach" als package->redir->in speichert
		//muss aber noch als char * abgespeichert werden
		return INFILE;
	}
	else if (current_process[(*i)] == '>')
	{
		if (current_process[(*i) + 1] == '>')
		{
			(*i)++;
			// printf("input>>: 	%s\n", input);
			//function die "des danach" als package->redirection speichert
			//muss aber noch als char * abgespeichert werden
			return APPEND;
		}
		// printf("input>: 	%s\n", input);
		//function die "des danach" als package->redirection speichert
		//muss aber noch als char * abgespeichert werden
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

char	*check_redirections(t_package **newNode, char *current_process)
{
	int i = 0;
	int iR = 0;
	int oR = 0;
	int operator = NOTHING;
	char	*remainder;
	remainder = ft_calloc(ft_strlen(current_process) + 1, sizeof(char));
	int		remainder_index = 0;

	(*newNode)->outfiles = malloc(sizeof(char *) * 256);
	(*newNode)->infiles = malloc(sizeof(char *) * 256);
	// function that checks how many reds there are
	// @Alex kann auch jmd red ohne filename eingeben - if - was dann???
	// ->dann kann das nciht geöffnet werden
	(*newNode)->out_redirection = malloc(sizeof(int) * 256);
	(*newNode)->in_redirection = malloc(sizeof(int) * 256);
	// check max files in process and maybe use ft_calloc
	// b-zero package setzt nur den **in/out auf 0 nicht dem seine elemente
	while (current_process[i])
	{
		operator = char_compare(current_process, &i);
		if (operator == INFILE || operator == HEREDOC)
		{
			(*newNode)->in_redirection[iR] = operator;
			(*newNode)->infiles[iR] = get_file(current_process, &i);
			// i steht auf dem meta_char
			iR++;
		}
		else if (operator == TRUNCATE || operator == APPEND)
		{
			(*newNode)->out_redirection[oR] = operator;
			(*newNode)->outfiles[oR] = get_file(current_process, &i);
			oR++;
		}
		// if (operator)
			// printf("hier:	%c\n", current_process[i]);
		remainder[remainder_index] = current_process[i];
		remainder_index++;
		i++;
	}
	printf("remainder %s\n", remainder);
	(*newNode)->in_redirection[iR] = NOTHING;
	(*newNode)->out_redirection[oR] = NOTHING;
	(*newNode)->infiles[iR] = NULL;
	(*newNode)->outfiles[oR] = NULL;
	return (remainder);
}



void	fill_package(t_package **newNode, char *current_process)
{
	char	*cmd_tokens;
	
	cmd_tokens = check_redirections(newNode, current_process);
	(*newNode)->cmd_args = ft_split(cmd_tokens, ' ');
	(*newNode)->cmd = (*newNode)->cmd_args[0];
	//special split && cmd abspeichern!
	
	printf("\n");
	for (int i = 0; (*newNode)->out_redirection[i] != 0; i++)
		printf("out_redirection[%d] = %d\n", i , (*newNode)->out_redirection[i]);
	for (int i = 0; (*newNode)->in_redirection[i] != 0; i++)
		printf("in_redirection[%d] = %d\n", i , (*newNode)->in_redirection[i]);
	for	(int i = 0; (*newNode)->infiles[i] != NULL; i++)
		printf("infiles[%d] = %s\n", i , (*newNode)->infiles[i]);
	for	(int i = 0; (*newNode)->outfiles[i] != NULL; i++)
		printf("outfiles[%d] = %s\n", i , (*newNode)->outfiles[i]);
	
	// //functions die eine nach der anderen input-rules anwenden
	// //und ein nach dem anderen package value bestücken
	// if (operator == TRUNCATE)
	// 	//function die "des danach" als package->redirection speichert
	// if (operator == APPEND)

	// if (operator == INFILE)

	// if (operator == HEREDOC)

	// (*newNode)->cmd = ft_strdup(input);
	// //muss der est ohhne redirections sein
	// //freen - aber spater dann beim listen leeren
	// (*newNode)->redirection = operator;
	// if (operator == PIPE)
	// 	(*newNode)->pipe = true;
	// else
	// 	(*newNode)->pipe = false;
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
	//zeile die neue node dran hängt
	newNode->next = NULL;
	return (0);
}