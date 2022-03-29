/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:11 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 23:22:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*empty_case(int index, char *tmp, int fd[], char *str_final)
{
	index += ft_strlen(tmp);
	write(fd[1], tmp, ft_strlen(tmp));
	str_final = ft_strcalloc(index);
	if (read(fd[0], str_final, index) == -1)
		perror("failed");
	free(tmp);
	close(fd[1]);
	close(fd[0]);
	return (str_final);
}

static void	prep_str(char **tmp, char *str)
{
	free((*tmp));
	(*tmp) = 0;
	(*tmp) = ft_strdup(ft_strchr(str, '='));
}

char	*exp_special_case(char *str, int end)
{
	int		index;
	char	*tmp;
	char	*str_final;
	int		fd[2];

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
		write(fd[1], tmp, ft_strlen(tmp));
	}
	if (tmp != NULL)
	{
		prep_str(&tmp, str);
		str_final = empty_case(index, tmp, fd, str_final);
	}
	return (str_final);
}

bool	check_same_var(t_envlist **head, char *str)
{
	bool		same;
	t_envlist	*tmp_list;
	char		*test_str;

	same = false;
	tmp_list = (*head);
	if (!str)
		return (same);
	test_str = ft_strcalloc(ft_strlen_c(str, '=') + 1);
	ft_strlcpy(test_str, str, ft_strlen_c(str, '=') + 1);
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(tmp_list->content, test_str, ft_strlen(test_str))
			&& tmp_list->content[ft_strlen(test_str)] == '=')
		{
			same = true;
			ft_change_var(&tmp_list->content, str);
			free(test_str);
			return (same);
		}
		tmp_list = tmp_list->next;
	}
	free(test_str);
	return (same);
}
