/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/13 15:57:52 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//testing out readline functon

#include "minishell.h"

void set_user()
{
	char path[200];

	getcwd(path, BUFF);
	printf("%sminishell@rschleic&mjeyavat%s>%s%s%s", CYN, RESET, BLU, path, RESET);
}

int main()
{
	char *inpt;
	
	while (1)
	{
		set_user();
		//after that, prompt s been created
		inpt = readline("$");
		init_lex(&inpt);
		printf("inpt = %s\n", inpt);
		// we must free input (requierd by readline)
		add_history(inpt);
		//how to implement a working history?? (done 60%);
		//but how?
		// printf("%s", inpt);
		// printf("\n");
	}
	return 0;
}
