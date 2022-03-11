#include "minishell.h"


void	write_in_pipe(char *str, int *i, int *fd, int	*len)
{
		write(fd[1], &str[(*i)], 1);
		(*len)++;
		(*i)++;
}

void	handle_sq(char *str, int *i, int *fd, int	*len)
{
	(*i)++;
	while (str[(*i)] != -1 && str[(*i)] != '\0')
		write_in_pipe(str, i, fd, len);
	(*i)++;
}

void	handle_dq(char *str, int *i, int *fd, int	*len)
{
	printf("02\n");
	(*i)++;
	while (str[(*i)] != -2)
	{
		if (str[(*i)] != '$')
			write_in_pipe(str, i, fd, len);
		// if (str[(*i)] == '$')
			// expand_function(str, &i, fd, &len);
	}
	(*i)++;
}

void	search_for_dollar_quotes(char *str, int *fd, int *len)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -1)
			handle_sq(str, &i, fd, len);
		else if (str[i] == -2)
			handle_dq(str, &i, fd, len);
		// else if (str[i] == '$')
			// expand_function(str, &i, fd, &len);
		else if (str[i] != '$')
			write_in_pipe(str, &i, fd, len);
	}
}


void	clean_expand(char	**origin, t_builtin *builtin)
{
	int		i;
	int		fd[2];
	int		len;
	char	*tmp;

	
	i = 0;
	len = 0;
	(void)builtin;
	// if (!ft_strchr(origin[i], '$') && !ft_strchr(origin[i], -2) && !ft_strchr(origin[i], -1))
	// {
	// 	printf("do you go in here\n");
	// 	i++;
	// }
	//brauchs theoretisch nicht
	if (pipe(fd) == -1)
		write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
		//error code
	while (origin[i] != NULL)
	{
		search_for_dollar_quotes(origin[i], fd, &len);
		tmp = origin[i];
		origin[i] = ft_strcalloc(len);
		read(fd[0], origin[i], len);
		free(tmp);
		i++;
	}
}

// void	write_in_pipe(char *str, int *i, int *fd, int	*len)
// {
// 	(*i)++;
// 	while (str[(*i)] != '\'' && str[(*i)] != '\0')
// 	{
// 		write(fd[0], str[(*i)], 1);
// 		(*len)++;
// 		(*i)++;
// 	}
// 	(*i)++;
// }
// //uberspringt immer die quote

// void	search_for_dollar_quotes_2(char *str, int *fd, int *len)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == -1)
// 		{
// 			i++;
// 			while (str[i] != -1 && str[i] != '\0')
// 				write_in_pipe(str, &i, fd, &len);
// 			i++;
// 		}

// 		//handle_single_quotes_function
// 		else if (str[i] == -2)
// 		{
// 			i++;
// 			while (str[i] != -2)
// 			{
// 				if (str[i] != '$')
// 					write_in_pipe_2(str, &i, fd, &len);
// 				if (str[i] == '$')
// 					expand_function(str, &i, fd, &len);
// 			}
// 			i++;
// 		}
// 		//handle_double_quotes_function
// 		else if (str[i] != '$')
// 			write_in_pipe_2(str, &i, fd, &len);
// 		else if (str[i] == '$')
// 			expand_function(str, &i, fd, &len);
// 	}
// }


// void	search_for_dollar_quotes(char *str, int *fd, int *len)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == -1 && str[i] != '\0')
// 		{
// 			write_in_pipe(str, &i, fd, &len);
// 			// i++;
// 			// while (str[i] != '\'' && str[i] != '\0')
// 			// {
// 			// 	write(fd[0], str[i], 1);
// 			// 	len++;
// 			// 	i++;
// 			// }
// 			// i++;
// 		}
// 		else if (str[i] == -2 && str[i] != '\0')
// 		{

// 		}

// 	}
// }

//fsanitize=address problems!
