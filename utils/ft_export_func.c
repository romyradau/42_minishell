
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

	index = 0;
    if (!str) {
        return 0;
    }
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
		if (!simple_check(tmp))
			return (NULL);
		index += ft_strlen(tmp);
		if (write(fd[1], tmp, ft_strlen(tmp)) == -1)
			perror("failed");
	}
	if (tmp != NULL)
	{
		free(tmp);
		tmp = 0;
		tmp = ft_strdup(ft_strchr(str, '='));
		index += ft_strlen(tmp);
		write(fd[1], tmp, ft_strlen(tmp));
		str_final = ft_strcalloc(index);
		if (read(fd[0], str_final, index) == -1)
			perror("failed");
		free(tmp);
		close(fd[1]);
		close(fd[0]);
	}
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
				fprintf(stderr ,"export: %s: not a valid identifier\n", str);
				g_exit_stat = 1;
				return (NULL);
			}
			free(anws);
			return (str);
		}
		return (anws);
	}
	else if ((ft_isalpha(str[0]) || str[0] == '_') && !ft_strchr(str, '='))
		return (str);
	fprintf(stderr, "export: %s: not a valid identifier\n", str);
	g_exit_stat = 1;
	return (NULL);
}

int ft_change_var(char **str1, char *str2)
{
	char		*tmp;
	
	tmp = (*str1);
	(*str1) = ft_strdup(str2);
	free(tmp);
	return (1);
}


bool check_same_var(t_envlist **head, char *str)
{
	bool	same;
	t_envlist *tmp_list;
	int			i;
	char *test_str;

	same = false;
	tmp_list = (*head);
	i = 0;
	if (!str)
		return (same);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	test_str = ft_strcalloc(i);
	ft_strlcpy(test_str, str, i);
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(tmp_list->content, test_str, ft_strlen(test_str)) && tmp_list->content[ft_strlen(test_str)] == '=')
		{
			same = true;
			printf("FOUND : %s\n",test_str);
			printf("CONTENT: %s\n", tmp_list->content);
			ft_change_var(&tmp_list->content, str);
			printf("CONTENT: %s\n", tmp_list->content);
            free(test_str);
			return (same);
		}
		tmp_list = tmp_list->next;
	}
    free(test_str);
	return (same);
}

int ft_export(t_envlist **head, t_package *package, char ***env_cpy)
{
	char *str;

	str = input_checker(package->cmd_args[1]);
	if (check_same_var(head, str))
		return (1);
	if (str == NULL)
		return (0);
	if (add_node(head, str))
	{
		update_new_env(env_cpy, (*head));
		return (1);
	}
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

int print_export(t_builtin *builtin)
{
	t_envlist *tmp;
	if (builtin->env_list == NULL)
	{
		return (0);
	}
	tmp = builtin->env_list;
	while(tmp != NULL)
	{
		write(1, "declare -x ", 12);
		ft_putstr_fd(tmp->content, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (1);
}
