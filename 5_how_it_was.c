#include "minishell.h"

int expand_result_standart(char **res, t_builtin *builtin)
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
	//*find "$" singe
	while (res[i] != NULL)
	{
		if (ft_strchr(res[i], -1) && res[i][j] != '\0')
 		{
 			tmp = res[i];
 			res[i] = ft_strtrim(tmp, "\xFF");
 			// ist jetzt hier nicht nullterminiert etc
 			free(tmp);
 		}
		else if (ft_strchr(res[i], -2) && res[i][j] != '\0')
		{	
			tmp = res[i];
 			res[i] = ft_strtrim(tmp, "\xFE");
 			// ist jetzt hier nicht nullterminiert etc
 			free(tmp);
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
			printf("res[i]: %s\n", res[i]);
			if (res[i][j] == '$' && res[i][j + 1] == '\0')
				return (1);
			while (res[i][j] != '\0' && res[i][j] != '$')
			{
				write(fd[1], &res[i][j], 1);
				j++;
				count++;
				if (res[i][j] == '$')
					break;
			}
			if (complex_expand(&res[i], fd, &count, tmp_list) == 0)
			{
				printf("Res[i][j]: %c\n", res[i][j]);
				// while (res[i][j] != '\0')
				// {
				// 	write(fd[1], &res[i][j], 1);
				// 	count++;
				// 	j++;
				// }
				tmp = res[i];

			// free(res[i]);
				res[i] = ft_strcalloc(count);
				if (read(fd[0], res[i], count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				res[i][j] = '\0';
 				// ist jetzt hier nicht nullterminiert etc
 				free(tmp);
			}
		}
		else if (ft_strchr(res[i], '$'))
		{
			if (pipe(fd) == -1)
				write(2, "Error: tmp_pipe creation unsuccessfull\n", 40);
				//hier noch die dollar dollar billion scheisse einfugen
			if (res[i][j] == '$' && res[i][j + 1] == '\0')
				return (1);
			while (res[i][j] != '\0' && res[i][j] != '$')
			{
				write(fd[1], &res[i][j], 1);
				j++;
				count++;
				if (res[i][j] == '$')
					break;
			}
			//part der alles vr $ in pipe schreibt
			// env_start = ft_strdup(complex_expand(&res[i], '$', &cnt, fd));
			// if (!env_start)
			// 	return (0);
			if (complex_expand(&res[i], fd, &count, tmp_list) == 0)
			{
				if (res[i][j] == '$' && (res[i][j + 1] == '\0'))
				{
					printf("Res[i][j]: %c\n", res[i][j]);
					write(fd[1], &res[i][j], 1);
					count++;
					j++;
				}
				tmp = res[i];
			// free(res[i]);
				res[i] = ft_strcalloc(count);
				if (read(fd[0], res[i], count) == -1)
					return (0);
				close(fd[0]);
				close(fd[1]);
 				res[i][j] = '\0';
 				// ist jetzt hier nicht nullterminiert etc
 				free(tmp);
			}
 			// res[i][j] = '\0';
		}
		printf("rEs[i]: %s\n", res[i]);
		i++;
	}
	return (0);
}