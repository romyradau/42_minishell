/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:59:52 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/02/10 20:25:47 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#endif

#ifndef BUFF
# define BUFF 200
#endif

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
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
}	t_pipe;

typedef struct s_comands
{
	char *cmd;
	char *cmd_flag;
	char *cmd_args;
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
=======
typedef struct s_data
{
	int			amount_tokens;
	t_token 	*token;
	t_commands 	*cmd;
	t_pipe 		*pipe;
} t_data;


//====================FUNCTIONS=========
void init_lex(char **input);
int count_quots(t_data *data, char c);

//====================FUNCTIONS=========


