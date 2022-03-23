
#include "../minishell.h"

//TODO: Extra Function aussagen dies das merk dia 
/*        bsp                       *
 *   bash-3.2$ export !Hallo        *
 *   bash: !Hallo: event not found  *
*/

//TODO: export + sing rules
/*
	*rule 1: darf nicht vorne sein (handelt) oder mitten drin (muss noch gehandelt werden)
	*rule 2: darf nur vor dem isgleich sign aber muss weg gemacht werden
	*rule 3: darf nach dem istgleich sein.
	*rule 4: der scheis muss in einer while loop laufen mon amie
*/

int simple_check(char *str)
{
	int index;

	index = 1;
	while (str[index] != '\0' && (str[index] == '_' || ft_isalnum(str[index])))
	{
		printf("str[%d] : %c\n", index, str[index]);
		index++;
	}
	if (index == (int)ft_strlen(str))
		return (1);
	return (0);
}

static char *exp_special_case(char *str, int end)
{
	int 	index;
	char	*tmp;
	char	*str_final;
	int 	fd[2];

	index = 0;
	tmp = NULL;
	str_final = NULL;
	if (end <= 1)
		return (NULL); 
	if (str[(end - 1)] == '+')
	{
		pipe(fd);
		tmp = ft_strtrim(str, ft_strchr(str, '+'));
		printf("tmp: %s\n", tmp);
		if (!simple_check(tmp))
			return (NULL);
		index += ft_strlen(tmp);
		if (write(fd[1], tmp, ft_strlen(tmp)) == -1)
			perror("failed");
	}
	if (tmp != NULL)
	{
		printf("specail case has been found\n");
		free(tmp);
		tmp = 0;
		tmp = ft_strdup(ft_strchr(str, '='));
		index += ft_strlen(tmp);
		write(fd[1], tmp, ft_strlen(tmp));
		printf("tmp: %s\n", tmp);
		str_final = ft_strcalloc(index);
		if (read(fd[0], str_final, index) == -1)
			perror("failed");
		free(tmp);
		close(fd[1]);
		close(fd[0]);
	}
	printf("tmp_final: %s\n", str_final);
	return(str_final);
}

char *input_checker(char *str)
{
	int end;
	char *anws;

	anws = NULL;
	end = 0;
	if ((ft_isalpha(str[0]) || str[0] == '_') && ft_strchr(str, '='))
	{
		printf("input checker is running\n");
		while (str[end] != '=' && str[end] != '\0')
			end++;
		anws = exp_special_case(str, end);
		if (!anws)
		{
			anws = ft_strtrim(str, ft_strchr(str, '='));
			if (!simple_check(anws))
			{
				if (anws[0] == '_')
				{
					free(anws);
					return (str);
				}
				free (anws);
				printf("export: %s: not a valid identifier\n", str);
				g_exit_stat = 1;
				return (NULL);
			}
			free(anws);
			return (str);
		}
		return (anws);
	}
	printf("export: %s: not a valid identifier\n", str);
	g_exit_stat = 1;
	return (NULL);
}

int ft_export(t_envlist **head, t_package *package)
{
	char *str;
	str = input_checker(package->cmd_args[1]);
	if (str == NULL)
		return (0);
	if (add_node(head, str))
			return (1);
	if (ft_isdigit(package->cmd_args[1][0]))
	{
		//TODO: in write
		printf("bash: export: %s: not a valid identifier\n", package->cmd_args[1]);
		g_exit_stat = 1;
		return (g_exit_stat);
	}
	else if (!ft_strchr(package->cmd_args[1], '='))
		return (1);
	return (0);
}