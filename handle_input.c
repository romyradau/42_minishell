/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:59 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/16 17:44:18 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
  see if those are valid cmd
  safe them to struct
*/
// int check_quotes(t_data *data, char c)
// {

// 	bool	sq;
// 	bool	dq;


//     while(i < data->amount_tokens)
//     {
//         j = 0;
//         while (data->token->token_list[i][j])
//         {
//             if (data->token->token_list[i][j] == c)
//                 quots++;
//             j++;
//         }
//         i++;
//     }
//     return(quots);
// }

// void init_lex(char **input)
// {
    
//     t_data *data;
//     char **full_str;
//     int i;
    
//     i = 0;
//     full_str = ft_split((*input), ' ');
//     data = (t_data *)malloc(sizeof(full_str));
//     if (!data)
//         return; 
//     data->token = (t_token *)malloc(sizeof(char **));
//     if (!data->token)
//         return;
//     data->token->token_list = full_str;
//     while(data->token->token_list[i])
//     {
//         printf("%s\n", data->token->token_list[i]);
//         i++;
//     }
//     data->amount_tokens = i;
//     //test
//     printf("command amount %d\n", data->amount_tokens);
//     printf("there are %d quots\n", count_quots(data, '"'));
// }

/*
shell gets input
ignores it if # in the beginning
devides input in words and operators
These tokens are separated by metacharacters
employs quoting rules on the words and characters
*/

/*
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
anfuhrungszeichen und spaces entfernen bei weirden langen commands ???
*/