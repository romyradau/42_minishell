/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:59 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/10 19:01:53 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/**
 * see if those are valid cmd
 * safe them to struct
*/

void init_pars(char **tokens)
{
    //t_commands *cmd;
    char **full_str;
    int i;
    
    i = 0;
    full_str = ft_split((*tokens), ' ');
    while(full_str[i])
    {
        printf("%s\n", full_str[i]);
        i++;
    }
}

/*
shell gets input
ignores it if # in the beginning
devides input in words and operators
employs quoting rules on the words and characters
*/

/*
Breaks the input into words and operators, obeying the quoting rules
These tokens are separated by metacharacters
quoting rules:
1.quotes - double -single
1.2 env Variables
2.herdoc
3.redirections
4.pipes
5.cmds -args
6.eigene commands
extra stuff 
$?
anfuhrungszeichen und spaces entfernen bei weirden langen commands
*/


/*
parses tokens in commands
*/