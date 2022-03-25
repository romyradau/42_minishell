#include "minishell.h"

void	get_exit_status(int n, int fd, t_exp *exp)
{
	char	c;

	if (n < 0)
	{
		n = n * (-1);
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n = 147483648;
		}
	}
	if (n / 10 > 0)
	{
		get_exit_status((n / 10), fd, exp);
		exp->len++;
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

char	*simple_expand(const char *s, int c)
{
	char			ch;
	char			*str;
	unsigned int	cnt;

	cnt = 0;
	ch = (char) c;
	str = (char *)s;
	while (*str != ch)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	if (*str + 1 != ' ')
		return (str + 1);
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

int str_envlen(char *str, unsigned char c)
{
	int i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return i;
}


int	complex_expand(char *str, t_exp *exp, t_envlist *tmp_list)
{
	int		end_of_var;
	int		count;

	if (str[exp->i + 1] != ' ')
		exp->i++;
	else
		return (0);
	if (str[exp->i] == '?' && str[exp->i + 1] == '\0')
	{
		printf("exit: %d\n", g_exit_stat);
		get_exit_status(g_exit_stat, exp->fd[1], exp);
		return (1);
	}
	count = 0;
	end_of_var = exp->i;
	while (str[end_of_var] != '\0' 
		&& (ft_isalnum(str[end_of_var]) || str[end_of_var] == '_'))
	{
		end_of_var++;
		count++;
	}	
	while (tmp_list != NULL && count)
	{
		if (!ft_strncmp(tmp_list->content, &str[exp->i], str_envlen(tmp_list->content, '=')) 
			&& (str_envlen(tmp_list->content, '=') == count))
		{
			if (!do_the_expansion(tmp_list, exp, end_of_var))
				return (0);
		}
		tmp_list = tmp_list->next;
	}
	exp->i += count;
	return (1);
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
