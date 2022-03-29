#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/wait.h>
# include <string.h>
# include <limits.h>
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

int	g_exit_stat;

typedef enum meta{
	NOTHING,
	PIPE,
	TRUNCATE,
	INFILE,
	APPEND,
	HEREDOC,
}	t_meta;

typedef struct s_expandables{
	int		i;
	int		fd[2];
	int		len;
}	t_exp;

typedef struct s_file{
	int		in;
	int		out;
	int		of;
	int		infile;
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
	int		in;
	int		out;
}	t_red;

typedef struct s_envlist
{
	char				*content;
	bool				hiden;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}	t_envlist;

typedef struct s_builtin
{
	char		*home_path;
	t_envlist	*env_list;
}	t_builtin;

typedef struct s_package
{
	int					*in_redirection;
	char				**infiles;
	int					*out_redirection;
	char				**outfiles;
	bool				pipe;
	char				*cmd;
	char				**cmd_args;
	t_builtin			*builtin;
	struct s_package	*next;
}	t_package;

typedef struct s_data
{
	int					packages;
	char				**processes;
	char				**env;
	t_package			*head;
	t_package			*orig_head;
	t_file				file;
}	t_data;

/*====================FUNCTIONS=========*/

void		init_lex(char **input);
char		*cut_quot_sequence(char *str, char c);
char		*get_path(char **env, const char *search_str);
int			builtin_picker(t_package *package, t_builtin *builtin, char ***env_cpy);
void		btn_handler(int sig);
int			prep_signal(t_data *data);
int			handle_input(t_data *data, t_builtin *builtin, char ***env_cpy);
char		**special_pipe_split(char const *s, char c);
char		**special_cmd_split(char const *s, char c);
void		kill_d_str(char **str);
int			check_if_builtin(t_package *package);
void		free_packages(t_data *data);
int			prepare_packages(t_data *data, char *input);

/*====================PARSING=========*/

int			process_packages(t_data *data, t_builtin *builtin);
int			fill_package(t_package **new, char *current, t_builtin *builtin);
t_package	*print_package_normal(t_package *head, t_builtin *builtin);
t_package	*print_package_builtin(t_package *head, t_builtin *builtin);
void		print2Darray(char **split);
char		*get_command(t_package **newNode, char *current_process);
bool		is_metachar(char c);
bool		single_quotes(char *s, t_red **red, int *i);
bool		double_quotes(char *s, t_red **red, int *i);
void		skip_sq(char *s, int *i);
void		skip_dq(char *s, int *i);
int			trim_and_expand(char **res, t_builtin *builtin);
void		clean_expand(char	**origin, t_builtin *builtin);
void		get_exit_status(int n, int fd, t_exp *exp);
void		ft_sigchild(int sig);
void		sig_quit(int sig);
void		close_herdoc(int sig);
int			manage_red_files(t_package **newNode, char *current, t_red *red);
int			complex_expand(char *str, t_exp *exp, t_envlist *tmp_list);
int			end_of_env_var(t_exp *exp, char *str, int *count, int *end_of_var);
void		write_in_pipe(char *str, t_exp *exp);

/*====================BUILTIN==========*/

int			check_quot_sequence(char *str, char c, bool *q);
char		*cut_quot_sequence(char *str, char c);
char		*handle_qouts(char **cmd_arg, int index);
char		*ft_strcalloc(int size);
int			doublestr_len(char **cmd_arg);
int			ft_strlen_c(char *str, char c);
int			cmd_variants(char *str, const char *str2, unsigned int len);
int			check_for_flag(char *str, bool *flag);
void		ft_echo(char **output, bool flag, t_package *package);
int			prep_echo(t_package *package, bool flag);
int			prep_cd(t_package *package, t_builtin *builtin);
int			call_pwd();
int			ft_equel_check(char *str, int c);
int			set_envlist(t_data *data, t_envlist **list);
int			del_env_node(t_envlist **list, int len, t_envlist *tmp);
int			del_lasnode(t_envlist **l, const char *arg, char ***env_cpy, t_envlist *tmp);
int			print_env(t_builtin *builtin);
int			ft_unset(t_envlist **list, const char *arg, char ***env_cpy);
int			add_node(t_envlist **head, const char *src);
int			reverse_envlist(t_envlist **list);
t_envlist	*creat_node(const char *src);
int			simple_check(char *str);
char		*exp_special_case(char *str, int end);
int			ft_change_var(char **str1, char *str2);
bool		check_same_var(t_envlist **head, char *str);
int			ft_export(t_envlist **head, t_package *package, char ***env_cpy);
int			expand_function(char *str, t_exp *exp, t_builtin *builtin);
int			print_export(t_builtin *builtin);
void		set_new_env(char ***cpy_envp, t_envlist *env_list);
int			env_list_len(t_envlist *list);
int			update_new_env(char ***cpy, t_envlist *envlist);
int			if_ans_wrong(char **str, char **anws);
/*====================EXECUTION=========*/

void		init_redirections(t_file *ret);
int			links(t_file *file, t_package *current);
int			rechts(t_file *file, t_package *current);
void		execute(t_data *data, t_builtin *bi, t_file *file, char ***env_cpy);
void		sig_in_heredoc(int sig);
void		set_attr(void);
void		unset_attr(t_package *package);
void		set_termios(void);
void		exec_packages(char *in, t_data *data, t_builtin *bi, char ***env_cpy);
void		redirect_parent(t_file *file);
void		do_the_execution(t_package *current, char **envp, t_data *data);
void		open_heredoc(char *limiter, t_file *file);
void		dup2_protection(int *fd, int aim);

/*====================CALCULATING=========*/

int			allocate_redirections(t_package **newNode, char *current_process);
bool		is_metachar(char c);
int			char_compare(char *current_process, t_red **red, int *i);
int			str_envlen(char *str, unsigned char c);
int			ft_exit(t_package *package);

#endif
