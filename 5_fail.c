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

void	trim_quotes(char **origin, char	q)
{
	char	*tmp;

	tmp = (*origin);
	if (q == -1)
		(*origin) = ft_strtrim(tmp, "\xFF");
	else if (q == -2)
		(*origin) = ft_strtrim(tmp, "\xFE");
	// ist jetzt hier nicht nullterminiert etc
	free(tmp);
}

void	fill_pipe(char **origin, int *fd, int *j, int *count)
{
	while ((*origin)[(*j)] != '\0' && (*origin)[(*j)] != '$')
	{
		write(fd[1], &(*origin)[(*j)], 1);
		j++;
		(*count)++;
		if ((*origin)[(*j)] == '$')
			break;
	}
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
	while ((*origin) != NULL)
	{
		if ((*origin)[j] == -1 && (*origin)[j] != '\0')
			trim_quotes(origin, -1);
		else if (ft_strchr((*origin), '$') && (*origin)[j] == -2)
		{	
			trim_quotes(origin, -2);
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			if ((*origin)[j] == '$' && (*origin)[j + 1] == '\0')
				return (1);
			fill_pipe(origin, fd, &j, &count);
			// while ((*origin)[j] != '\0' && (*origin)[j] != '$')
			// {
			// 	write(fd[1], &(*origin)[j], 1);
			// 	j++;
			// 	count++;
			// 	if ((*origin)[j] == '$')
			// 		break;
			// }
			if (complex_expand(&(*origin), fd, &count, tmp_list) == 0)
			{
				tmp = (*origin);
				(*origin) = ft_strcalloc(count);
				if (read(fd[0], (*origin), count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				(*origin)[j] = '\0';
 				free(tmp);
			}
		}
		else if (ft_strchr((*origin), '$'))
		{
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			if ((*origin)[j] == '$' && (*origin)[j + 1] == '\0')
				return (1);
			fill_pipe(origin, fd, &j, &count);
			if (complex_expand(&(*origin), fd, &count, tmp_list) == 0)
			{
				if ((*origin)[j] == '$' && ((*origin)[j + 1] == '\0'))
				{
					printf("(*origin)[j]: %c\n", (*origin)[j]);
					write(fd[1], &(*origin)[j], 1);
					count++;
					j++;
				}
				tmp = (*origin);
				(*origin) = ft_strcalloc(count);
				if (read(fd[0], (*origin), count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				(*origin)[j] = '\0';
 				free(tmp);
			}
		}
		printf("hallo\n");
		(*origin)++;
	}
	return (0);
}



// void	fill_pipe_start(char **origin, int *j)
// {
// 	while ((*origin)[j] != '\0' && origin[i][j] != '$')
// 	{
// 		write(fd[1], &origin[i][j], 1);
// 		j++;
// 		count++;
// 		if (origin[i][j] == '$')
// 			break;
// 	}	
// }