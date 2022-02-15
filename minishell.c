/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/15 19:12:42 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//testing out readline functon

#include "minishell.h"

void	print_package(t_package *head)
{
	while (head)
	{
		printf("prompt: %s\n", head->cmd);
		head = head->next;
	}
}

int	push_package(t_package **head, char *cmd)
{
	t_package *newNode;
	t_package *last;
	
	newNode = malloc(sizeof(t_package));
	if (newNode == NULL)
		return (1); 
	ft_bzero(newNode, sizeof(t_package));
	newNode->cmd = cmd;
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

int	prompt(t_package **package)
{
	char path[200];
	char *input;
	int id;
	char *user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	id = getpid();
	getcwd(path, BUFF);
	while(1)
	{
		signal(SIGINT, btn_handler);
		//printf("%s%s>%s%s%s", user, RESET, BLU, path, RESET);
		input = readline(user);
		printf("%s\n", input);
		if (push_package(package, input))
			return (1);
		print_package(package);
		add_history(input);
	}
	return (0);
}

int main()
{
	t_package	*package;
	
	package = NULL;
	
	if (prompt(&package))
	{
		//free
		//correct error message
		return(1);
	}
	
	//after that, prompt s been created
	//init_lex(&inpt);
	// we must free input (requierd by readline)
	//how to implement a working history?? (done 60%);
	//but how?
	// printf("%s", inpt);
	// printf("\n");
	return 0;
}
