#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef BUFF
# define BUFF 200
#endif

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>

//===============COLOR CODE=================================//
# define BLK		"\e[0;30m"
# define RED		"\e[0;31m"
# define GRN		"\e[0;32m"
# define YEL		"\e[0;33m"
# define BLU		"\e[0;34m"
# define MAG		"\e[0;35m"
# define CYN		"\e[0;36m"
# define WHT		"\e[0;37m"
# define RESET		"\033[0m"
//====================Sturcts==============================

typedef enum {
	NOTHING,
	PIPE,
	TRUNCATE,
	INFILE,
	APPEND,//>>
	HEREDOC
} meta;

typedef struct s_red{
	int		in;
	int		out;
	int		heredoc;
	char	*limiter;
	int		fd[2];
	int		tmp_fd;
	pid_t	pid;
}	t_red;
/**
 * this is our linked list which has simp cmd
*/
typedef struct s_package
{
	int					redirection;
	bool				pipe;
	char				*env_var;
	char				*cmd;
	char				**cmd_args;
	t_red				*redir;
//man könnte auch alles in eine struct hauen
	struct s_package	*next;
}	t_package;

typedef struct s_data
{
	int				packages;
	char			**env;
	t_package		*package;
}	t_data;


//====================FUNCTIONS=========

void init_lex(char **input);
int count_quots(t_data *data, char c);
void btn_handler(int sig);
int prompt();


//====================FUNCTIONS=========


#endif
