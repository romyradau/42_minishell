/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:59:52 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/13 22:16:41 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef BUFF
# define BUFF 200
#endif

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

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
}	t_pipe;
/**
 * this is our linked list which has simp cmd
*/
typedef struct simple_cmd
{
	char 				**cmd_arg;
	bool				pipe;
	struct simple_cmd 	*next;
    
}t_simple_cmd;

typedef struct s_data
{
	int				amount_scmd;
	char 			**env;
	t_simple_cmd 	*simp_cmd;
	
}t_data;


//====================FUNCTIONS=========
void init_lex(char **input);
int count_quots(t_data *data, char c);
void btn_handler(int sig);
void prompt();

//====================FUNCTIONS=========


#endif
