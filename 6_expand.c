#include "minishell.h"

int	end_of_env_var(t_exp *exp, char *str, int *count, int *end_of_var)
{
	if (str[exp->i] == '?' && str[exp->i + 1] == '\0')
	{
		get_exit_status(g_exit_stat, exp->fd[1], exp);
		return (1);
	}
	(*count) = 0;
	(*end_of_var) = exp->i;
	while (str[(*end_of_var)] != '\0'
		&& (ft_isalnum(str[(*end_of_var)]) || str[(*end_of_var)] == '_'))
	{
		(*end_of_var)++;
		(*count)++;
	}
	return (0);
}

int	expand_function(char *str, t_exp *exp, t_builtin *builtin)
{
	t_envlist	*tmp_list;

	tmp_list = builtin->env_list;
	if (str[exp->i] == '$' && str[exp->i + 1] == '\0')
		return (1);
	if (complex_expand(str, exp, tmp_list) == 0)
	{
		return (1);
	}
	return (0);
}
