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
	return (NULL);
}

int complex_expand(char **s,int *fd, int *count, t_envlist *tmp_list)
{

	char			*newS;
	int				cnt;
	int				tmp_i;
	char			*expand_content;
	char			*tmp;

	newS = (char *)(*s);
	cnt = 0;
	tmp_i = 0;
	while (*newS != '$')
	{	
		if (*newS == '\0')
			return (0);
		newS++;
		tmp_i++;
	}
	if (*(newS+1) != ' ' && *(newS + 1) != 0)
		newS++;
	else
		return (0);
	while(newS[cnt] != '\0' && (ft_isalnum(newS[cnt]) || newS[cnt] == '_'))
		cnt++;
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(tmp_list->content, newS, cnt))
		{
			expand_content = ft_strdup(simple_expand(tmp_list->content, '='));
			if (!expand_content)
				return (0);
			(*count) += ft_strlen(expand_content);
			free((*s));
			ft_putstr_fd(expand_content,fd[1]);
			while (newS[cnt] != '\0')
			{
				write(fd[1], &newS[cnt], 1);
				cnt++;
				(*count)++;
			}
			(*s) = ft_strcalloc((*count));
			if (!(*s))
				return (0);
			if (read(fd[0], (*s), (*count)) == -1)
				return (0);
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		tmp_list = tmp_list->next;
	}
	while (newS[cnt] != '\0')
	{
		write(fd[1], &newS[cnt], 1);
		cnt++;
		(*count)++;
	}
	tmp = (*s);
	(*s) = ft_strcalloc((*count));
	if (!(*s))
		return (0);
	if (read(fd[0], (*s), (*count)) == -1)
		return (0);
	(*s)[(*count)] = '\0';
	free(tmp);
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	trim_quotes(char **origin, int i,)
{
	char		*tmp;
	int			fd[2];
	int			i;
	int			j;
	int			len;

	if (pipe(fd) == -1)
		write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
	while (origin[i][j] != '\0')
	{
		if (origin[i][j] == '"')
		{
			j++;
			while (origin[i][j] != '"' && origin[i][j] != '\0')
			{
				if (origin[i][j] == '$')


				write(fd[0], &origin[i][j], 1);
				len;
				j++;
			}
			j++;
		}
		else if (origin[i][j] == '\'')
		{
			j++;
			while (origin[i][j] != '\'' && origin[i][j] != '\0')
			{
				write(fd[0], &origin[i][j], 1);
				len;
				j++;
			}
			j++;
		}	
		else
		{
			write(fd[0], &origin[i][j], 1);
			len;
			j++;
		}
	}
	close(fd[0]);
	close(fd[1]);
	tmp = origin[i];
	origin[i] = ft_strcalloc(len);
	if (read(fd[0], origin[i], len) == -1)
		return (0);
	// if (q == -1)
	// 	origin[i] = ft_strtrim(tmp, "\xFF");
	// else if (q == -2)
	// 	origin[i] = ft_strtrim(tmp, "\xFE");
	free(tmp);
}

int		pipe_single_dollar(char	**origin, int *fd, int i, int j)
{
	if (pipe(fd) == -1)
		write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
		//exit code
	if (origin[i][j] == '$' && origin[i][j + 1] == '\0')
		return (1);
	return (0);
}

int trim_and_expand(char **origin, t_builtin *builtin)
{
	t_envlist	*tmp_list;
	char		*tmp;
	int			fd[2];
	int			i;
	int			j;
	int			cnt;
	int			count;

	tmp_list = builtin->env_list;
	i = 0;
	j = 0;
	cnt = 0;
	count = 0;
	while (origin[i] != NULL)
	{
		// if (' und $)
		// // muss generell in trim quotes
		if ((ft_strchr(origin[i], '\'') || ft_strchr(origin[i], '"')) && !ft_strchr(origin[i], '$'))
		//Fall quotes aber kein dollar
			trim_quotes(origin, i);
		if ((ft_strchr(origin[i], '\'') || ft_strchr(origin[i], '"') && ft_strchr(origin[i], '$'))
		//Fall quotes und dollar
			trim_quotes(origin, i);
		//ob des jetzt dollar hat oder nicht ist egal
		else if (!ft_strchr(origin[i], '\'' && !ft_strchr(origin[i], '"' && ft_strchr(origin[i], '$')
		//Fall keine quotes aber dollar
		{
			if (pipe_single_dollar(origin, fd, i, j))
				return (1);
			while (origin[i][j] != '\0' && origin[i][j] != '$')
			{
				write(fd[1], &origin[i][j], 1);
				j++;
				count++;
				if (origin[i][j] == '$')
					break;
			}
			if (complex_expand(&origin[i], fd, &count, tmp_list) == 0)
			{
				if (origin[i][j] == '$' && (origin[i][j + 1] == '\0'))
				{
					write(fd[1], &origin[i][j], 1);
					count++;
					j++;
				}
				tmp = origin[i];
				origin[i] = ft_strcalloc(count);
				if (read(fd[0], origin[i], count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				origin[i][j] = '\0';
 				free(tmp);
			}
		}
		// if (origin[i][j] == -1 && origin[i][j] != '\0')
		// 	trim_quotes(origin, i, -1);
		else if (ft_strchr(origin[i], '$') && origin[i][j] != '\0')
			trim_quotes(origin, i, -2);
		else
		//heisst kein $ keine quotes
		// einfach nur trimmen nicht expanden 
		else if (ft_strchr(origin[i], '$') && origin[i][j] == -2)
		{	
			trim_quotes(origin, i, -2);
			if (pipe_single_dollar(origin, fd, i, j))
				return (1);
			while (origin[i][j] != '\0' && origin[i][j] != '$')
			{
				write(fd[1], &origin[i][j], 1);
				j++;
				count++;
				if (origin[i][j] == '$')
					break;
			}
			if (complex_expand(&origin[i], fd, &count, tmp_list) == 0)
			{
				if (origin[i][j] == '$' && (origin[i][j + 1] == '\0'))
				{
					write(fd[1], &origin[i][j], 1);
					count++;
					j++;
				}
				tmp = origin[i];
				origin[i] = ft_strcalloc(count);
				if (read(fd[0], origin[i], count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				origin[i][j] = '\0';
 				free(tmp);
			}
		}
		i++;
	}
	return (0);
}
