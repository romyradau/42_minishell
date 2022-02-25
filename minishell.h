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
	TRUNCATE, //>
	INFILE, //<
	APPEND, //>>
	HEREDOC //<<
} meta;

// typedef struct s_file{
// 	int		in;
// 	// data.in = open(package->in, O_RDONLY);
// 	int		out;
// 	// data.out = open(package->out, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	int		heredoc;
// 	char	*limiter;
// 	int		fd[2];
// 	int		tmp_fd;
// 	pid_t	pid;
// }	t_file;

typedef struct s_red{
	int		i;
	int		operator;
	int		left_over_index;
	char	*left_over;
	int		iR;
	int		oR;
}	t_red;
/*
wie man multiple redirections in der pipex struktur andert 
muss ich noch nachschauen
bis jetzt war es so anfang kann in oder herdoc sein udn ende das oufile
jetzt konnen solche redirections uberall stehen
*/

typedef struct s_package
{
	// infiles
	int					*in_redirection;	// [<,      <<,       <]
	char				**infiles;			// [ file1, heredoc, file2 ]

	// outfiles
	int					*out_redirection;
	char				**outfiles;

	bool				pipe;
	// char				*env_var;
	char				*cmd;
	char				**cmd_args;
	// t_file				*redir;
//man könnte auch alles in eine struct hauen
	struct s_package	*next;
}	t_package;

/**
 * this is our linked list 
*/
typedef struct s_data
{
	int				packages;
	char			**processes;
	char			**env;
	t_package		*head;
}	t_data;

typedef struct s_builtin
{
	char	*echo_str;
	//cd
	//pwd
	//env
}	t_builtin;

//====================FUNCTIONS=========

void	init_lex(char **input);
char	*cut_quot_sequence(char *str, char c);
int		builtin_picker(t_package *package);
void	btn_handler(int sig);
int		prompt();
char	**special_split(char const *s, char c);

//====================PARSING=========
// handle_input
int		push_package(t_package **head, char *current_process);
void	print_package(t_package *head);
void	print2Darray(char **split);


//====================PRINTING=========

void	print2Darray(char **split);
void	print_package(t_package *head);

#endif
