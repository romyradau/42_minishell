/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:03:47 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/09 16:38:26 by mjeyavat         ###   ########.fr       */
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
		inpt = readline("$");
		add_history(inpt);
		//printf("%s", inpt);
		printf("\n");
	}
	return 0;
}