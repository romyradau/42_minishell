/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:08:59 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/10 18:48:42 by mjeyavat         ###   ########.fr       */
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