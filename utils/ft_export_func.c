
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

int	simple_check(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index] != '\0' && (str[index] == '_' || ft_isalnum(str[index])))
	{
		// printf("str[%d] : %c\n", index, str[index]);
		index++;
	}
	if (index == (int)ft_strlen(str))
		return (1);
	return (0);
}

char	*input_checker(char *str)
{
	int		end;
	char	*anws;

	anws = NULL;
	end = 0;
	if ((ft_isalpha(str[0]) || str[0] == '_') && ft_strchr(str, '='))
	{
		end = ft_strlen_c(str, '=');
		anws = exp_special_case(str, end);
		if (if_ans_wrong(&str, &anws) == 0)
			return (anws);
		else
			return (str);
	}
	else if ((ft_isalpha(str[0]) || str[0] == '_') && !ft_strchr(str, '='))
		return (str);
	printf("export: %s: not a valid identifier\n", str);
	g_exit_stat = 1;
	return (NULL);
}

int	ft_change_var(char **str1, char *str2)
{
	char		*tmp;

	tmp = (*str1);
	(*str1) = ft_strdup(str2);
	free(tmp);
	return (1);
}

int	ft_export(t_envlist **head, t_package *package, char ***env_cpy)
{
	char	*str;

	str = input_checker(package->cmd_args[1]);
	if (check_same_var(head, str))
	{
		return (1);
	}
	if (str == NULL)
		return (0);
	if (add_node(head, str))
	{
		update_new_env(env_cpy, (*head));
		return (1);
	}
	if (ft_isdigit(package->cmd_args[1][0]))
	{
		printf("bash: export: %s: not a valid identifier\n",
			package->cmd_args[1]);
		g_exit_stat = 1;
		return (g_exit_stat);
	}
	else if (!ft_strchr(package->cmd_args[1], '='))
		return (1);
	return (0);
}

int	print_export(t_builtin *builtin)
{
	t_envlist	*tmp;

	if (builtin->env_list == NULL)
	{
		return (0);
	}
	tmp = builtin->env_list;
	while (tmp != NULL)
	{
		write(1, "declare -x ", 12);
		ft_putstr_fd(tmp->content, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (1);
}
