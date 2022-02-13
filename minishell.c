/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/13 22:24:20 by mjeyavat         ###   ########.fr       */
/*   Updated: 2022/02/13 15:57:52 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//testing out readline functon

#include "minishell.h"

void	prompt()
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
		add_history(input);
	}
}

int main()
{
		prompt();
		//after that, prompt s been created
		//init_lex(&inpt);
		// we must free input (requierd by readline)
		//how to implement a working history?? (done 60%);
		//but how?
		// printf("%s", inpt);
		// printf("\n");
	return 0;
}
