/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:59:52 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/10 19:57:44 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#endif

#ifndef BUFF
# define BUFF 200
#endif

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

//===============COLOR CODE=================================//
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"
//====================Sturcts==============================
typedef struct s_pipe{
	int		in;
	int		out;
	int		heredoc;
	char	*LIMITER;
	int		fd[2];
	int		tmp_fd;
	pid_t	pid;
	int		amount_cmd;
}	t_pipe;

typedef struct s_comands
{
    char *token;
    char *simple_command;
    t_pipe *pipe;   
    // struct s_comands *pre;
    // struct s_comands *next;
    
}t_commands;

typedef struct s_token
{
	char **token_list;
	// tbc
}t_token;

typedef struct s_env
{
	char	**env;
	
}

//====================FUNCTIONS=========