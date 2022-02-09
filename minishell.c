/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/09 18:47:55 by rschleic         ###   ########.fr       */
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
		// we must free input (requierd by readline)
		add_history(inpt);
		//how to implement a working history??
		//If you want the user to be able to get at the line later, (with C-p for example), you must call add_history () to save the line away in a history list of such lines.
		//but how?
		// printf("%s", inpt);
		// printf("\n");
	}
	return 0;
}
