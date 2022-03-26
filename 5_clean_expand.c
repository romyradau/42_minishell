#include "minishell.h"

void	write_in_pipe(char *str, t_exp *exp)
{
	write(exp->fd[1], &str[exp->i], 1);
	exp->len++;
	exp->i++;
}

void	handle_sq(char *str, t_exp *exp)
{
	exp->i++;
	while (str[exp->i] != -1 && str[exp->i] != '\0')
		write_in_pipe(str, exp);
	exp->i++;
}

void	handle_dq(char *str, t_exp *exp, t_builtin *builtin)
{
	exp->i++;
	while (str[exp->i] != -2)
	{
		if (str[exp->i] != '$')
			write_in_pipe(str, exp);
		if (str[exp->i] == '$')
		{
			if (expand_function(str, exp, builtin) == 0)
			{
				write_in_pipe(str, exp);
			}
		}	
	}
	exp->i++;
}

void	search_for_dollar_quotes(char *str, t_exp *exp, t_builtin *builtin)
{
	while (str[exp->i] != '\0')
	{
		if (str[exp->i] == -1)
			handle_sq(str, exp);
		else if (str[exp->i] == -2)
			handle_dq(str, exp, builtin);
		else if (str[exp->i] == '$')
		{
			if (expand_function(str, exp, builtin) == 1)
				write_in_pipe(str, exp);
		}
		else if (str[exp->i] != '$')
			write_in_pipe(str, exp);
	}
}

void	clean_expand(char	**origin, t_builtin *builtin)
{
	int		i;
	char	*tmp;
	t_exp	exp;

	i = 0;
	ft_bzero(&exp, sizeof(t_exp));
	while (origin[i] != NULL)
	{
		if (pipe(exp.fd) == -1)
			write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
		exp.i = 0;
		exp.len = 0;
		search_for_dollar_quotes(origin[i], &exp, builtin);
		tmp = origin[i];
		origin[i] = ft_strcalloc(exp.len + 1);
		if (exp.len)
			read(exp.fd[0], origin[i], exp.len);
		close(exp.fd[0]);
		close(exp.fd[1]);
		free(tmp);
		i++;
	}
}
//theoretisch kann man noch $$ als ID handlen...
