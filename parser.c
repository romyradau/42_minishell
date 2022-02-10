/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:06:29 by rschleic          #+#    #+#             */
/*   Updated: 2022/02/09 21:10:42 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


t_token lexer()

/*
parses tokens in commands
*/