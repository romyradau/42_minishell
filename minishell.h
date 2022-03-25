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
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <string.h>

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

int g_exit_stat;

typedef enum {
	NOTHING,
	PIPE,
	TRUNCATE, //>
	INFILE, //<
	APPEND, //>>
	HEREDOC, //<<
} meta;

typedef enum {
	EHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} builtin; 

typedef struct s_expandables{
	int		i;
	int		fd[2];
	int		len;
}	t_exp;

typedef struct s_file{
	int		in;
	// data.in = open(package->in, O_RDONLY);
	int		out;
	int		outfile;
	int		infile;
	// data.out = open(package->out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	int		heredoc;
	int		tmp_fd;
	char	*limiter;
	int		fd[2];
	pid_t	pid;
}	t_file;

typedef struct s_red{
	int		i;
	int		operator;
	int		left_over_index;
	char	*left_over;
	int		iR;
	int		oR;
}	t_red;

typedef struct s_envlist
{
	char *content;
	bool hiden;
	struct s_envlist *next;
	struct s_envlist *prev;
} t_envlist;

typedef struct s_builtin
{
	char		*home_path;
	t_envlist	*env_list;
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
	int					*in_redirection;	// [<,      <<,       <] // free
	char				**infiles;			// [ file1, heredoc, file2 ] // free

	// outfiles
	int					*out_redirection; //free
	char				**outfiles; //free

	bool				pipe;
	char				*cmd;
	char				**cmd_args;
	t_builtin			*builtin;
	struct s_package	*next;
}	t_package;

/**
 * this is our linked list 
*/
typedef struct s_data
{
	int						packages;
	char					**processes;
	char					**env;
	t_package				*head;
	struct	sigaction 		sa;
	struct	sigaction		cntrl_backslasch;
}	t_data;


/*====================FUNCTIONS=========*/

void	init_lex(char **input);
char	*cut_quot_sequence(char *str, char c);
char	*get_path(char **env, const char *search_str);
int		builtin_picker(t_package *package, t_builtin *builtin);
void	btn_handler(int sig);
int		prep_signal(t_data *data);
int		handle_input(t_data *data, t_builtin *builtin, char	**envp);
char	**special_pipe_split(char const *s, char c);
char	**special_cmd_split(char const *s, char c);
char	**kill_d_str(char **str);
int		check_if_builtin(t_package *package);
void	free_packages(t_data *data);
int		prepare_packages(t_data *data, char *input);


/*====================PARSING=========*/

int		process_packages(t_data *data, t_builtin *builtin);
// int		push_package(t_package **head, char *current_process);
int	fill_package(t_package **newNode, char *current_process, t_builtin *builtin);
// void	print_package(t_package *head);
t_package	*print_package_normal(t_package *head, t_builtin *builtin);
t_package	*print_package_builtin(t_package *head, t_builtin *builtin);
void	print2Darray(char **split);
char	*get_command(t_package **newNode, char *current_process);
// char *spot_quotes(char *str, char **str_wo_quotes, bool &sq, bool &dq);
bool	is_metachar(char c);
bool	single_quotes(char *s, t_red **red, int *i);
bool	double_quotes(char *s, t_red **red, int *i);
void	skip_sq(char *s, int *i);
void	skip_dq(char *s, int *i);
int		trim_and_expand(char **res, t_builtin *builtin);
void	clean_expand(char	**origin, t_builtin *builtin);
void	get_exit_status(int n, int fd, t_exp *exp);
void	ft_sigchild(int sig);
int		manage_red_files(t_package **newNode, char *current, t_red *red);


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
int		call_pwd(int fd);
int		set_envlist(t_data *data, t_envlist **list);
int 	print_env(t_builtin *builtin);
int		ft_unset(t_envlist **list, const char *arg);
char 	**cut_from_path(t_data *data, t_package *package);
int		add_node(t_envlist **head, const char *src);
int		ft_export(t_envlist **head, t_package *package);
int		expand_function(char *str, t_exp *exp, t_builtin *builtin);
int		print_export(t_builtin *builtin);




//====================EXECUTION=========

t_file	*init_redirections();
int		links(t_file *file, t_package *current);
int		rechts(t_file *file, t_package *current);
void	execute_function(t_data *data, char **envp, t_builtin *builtin, t_file *file);
void	sig_in_heredoc(int sig);
void	set_attr();
void	unset_attr();
void	execute_packages(char *input, t_data * data, t_builtin *builtin, char **envp);
int		redirect_parent(t_file *file);
void	do_the_execution(t_package *current, char **envp);


//====================PRINTING=========


void	print2Darray(char **split);
// void	print_package(t_package *head);

/*====================CALCULATING=========*/

int		allocate_redirections(t_package **newNode, char *current_process);
bool	is_metachar(char c);
int		char_compare(char *current_process, t_red **red, int *i);


#endif
