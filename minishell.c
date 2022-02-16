/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/16 15:11:04 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//testing out readline functon

#include "minishell.h"

int	prompt(void)
{
	char	path[200];
	char	*input;
	char	*user;
	struct sigaction sa;

	sa.sa_handler = btn_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	getcwd(path, BUFF);
	while (1)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (-1);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (-1);
		input = readline(user);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			return (1);
		}
		printf("%s\n", input);
		add_history(input);
	}
	return (0);
}

int	main(void)
{
	prompt();
	return (0);
}

/**
 * 		after that, prompt s been created
		init_lex(&inpt);
		we must free input (requierd by readline)
		how to implement a working history?? (done 60%);
		but how?
		printf("%s", inpt);
		printf("\n");
*/
