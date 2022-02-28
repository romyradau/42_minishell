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

typedef struct s_builtin
{
	char	**echo_str;
	//env
	char	*home_path;
}	t_builtin;

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
	// char				**env_var; //gibt vlt mehrere in einem package
	char				*cmd;
	char				**cmd_args;
	// t_file				*redir;
//man könnte auch alles in eine struct hauen
	t_builtin			*builtin; //TODO ->new Mohan (27.02.22)
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


/*====================FUNCTIONS=========*/

void	init_lex(char **input);
char	*cut_quot_sequence(char *str, char c);
char	*get_path(char **env, const char *search_str);
int		builtin_picker(t_package *package, t_builtin *builtin);
void	btn_handler(int sig);
int		prompt(t_data *data, t_builtin *builtin);
char	**special_split(char const *s, char c);

/*====================PARSING=========*/

int		process_packages(t_data *data);
// int		push_package(t_package **head, char *current_process);
void	fill_package(t_package **newNode, char *current_process);
void	print_package(t_package *head, t_builtin *builtin);
void	print2Darray(char **split);


//====================BUILTIN==========
int		check_quot_sequence(char *str, char c, bool *q);
char	*cut_quot_sequence(char *str, char c);
char	*handle_qouts(char **cmd_arg, int index);
char	*ft_strcalloc(int size);
int		doublestr_len(char **cmd_arg);
int 	ft_d_strlen(char **str);
char	**kill_d_str(char **str);
int		cmd_variants(char *str, const char *str2, unsigned int len);
int		check_for_flag(char *str, bool *flag);
void	ft_echo(char **output, bool flag, t_package *package);
int 	prep_echo(t_package *package, bool flag);
int 	prep_cd(t_package *package, t_builtin *builtin);
int		call_pwd(t_package *package, int fd);
//====================PRINTING=========

void	print2Darray(char **split);
// void	print_package(t_package *head);

/*====================CALCULATING=========*/

void	allocate_redirections(t_package **newNode, char *current_process);
bool	is_metachar(char c);
int		char_compare(char *current_process, int *i);


#endif
