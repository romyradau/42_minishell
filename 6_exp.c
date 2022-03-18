#include "minishell.h"

char	*simple_expand(const char *s, int c)
{
	char			ch;
	char			*newS;
	unsigned int	cnt;

	cnt = 0;
	ch = (char) c;
	newS = (char *)s;
	while (*newS != ch)
	{
		if (*newS == '\0')
			return (0);
		newS++;
	}
	if (*newS+1 != ' ')
		return (newS+1);
		//warum gucken wir hier ob nach dem = auch kein ws kommt?
	return (NULL);
}

int	do_the_expansion(t_envlist *tmp_list, t_exp *exp, int end_of_var)
{
	char	*expand_content;

	expand_content = ft_strdup(simple_expand(tmp_list->content, '='));
	if (!expand_content)
		return (1);
	exp->len += ft_strlen(expand_content);
	write(exp->fd[1], expand_content, ft_strlen(expand_content));
	free(expand_content);
	exp->i = end_of_var;
	return (0);
}

int complex_expand(char *str, t_exp *exp, t_envlist *tmp_list)
{
	int		end_of_var;
	int		count;

	if (str[exp->i + 1] != ' ' && str[exp->i + 2] != 0)
		exp->i++;
	else
		return (0);
	count = 0;
	end_of_var = exp->i;
	while(str[end_of_var] != '\0' && (ft_isalnum(str[end_of_var]) || str[end_of_var] == '_'))
	{
		end_of_var++;
		count++;
	}	
	while (tmp_list != NULL && count)
	{
		if (!ft_strncmp(tmp_list->content, &str[exp->i], count))
		{

			if (do_the_expansion(tmp_list, exp, end_of_var))
				return (0);
		}
				//hier brauchs ne ander fehlermeldung das ist fur wenn strdup fehlschlagt
				//generell nochmal eror anschauen
		tmp_list = tmp_list->next;
	}
	return (1);
}

int		expand_function(char *str, t_exp *exp, t_builtin *builtin)
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