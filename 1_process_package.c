/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_process_package.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:02:19 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 19:11:39 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**trim_spaces(t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->processes[i])
	{
		temp = data->processes[i];
		data->processes[i] = ft_strtrim(temp, " ");
		free(temp);
		i++;
	}
	return (data->processes);
}

int	fill_package(t_package **new, char *current, t_builtin *builtin)
{
	char	*full_cmd;
	char	*red_left_over;

	red_left_over = get_command(new, current);
	full_cmd = ft_strtrim(red_left_over, " ");
	free(red_left_over);
	if (full_cmd != NULL)
	{
		(*new)->cmd_args = special_cmd_split(full_cmd, ' ');
		clean_expand((*new)->cmd_args, builtin);
		(*new)->cmd = (*new)->cmd_args[0];
		free(full_cmd);
		return (1);
	}
	else
		return (0);
}

int	prep_push(t_package **head, t_package **last, t_data *data, t_package **new)
{
	if (*head == NULL)
	{
		*head = (*new);
		data->orig_head = *head;
		(*head)->next = NULL;
		return (0);
	}
	else
	{
		while ((*last)->next != NULL)
			(*last) = (*last)->next;
		(*last)->next = (*new);
		(*new)->next = NULL;
		return (0);
	}
	return (1);
}

int	push_package(t_package **head, char *curr, t_builtin *builtin, t_data *data)
{
	t_package	*new;
	t_package	*last;

	new = ft_calloc(sizeof(t_package), 1);
	if (new == NULL)
		return (1);
	ft_bzero(new, sizeof(t_package));
	if (fill_package(&new, curr, builtin))
	{
		last = *head;
		if (!prep_push(head, &last, data, &new))
			return (0);
	}
	else
		free(new);
	return (1);
}

int	parsepackages(t_data *data, t_builtin *builtin)
{
	t_package	*current_package;
	int			i;

	i = 0;
	while (data->processes[i])
	{
		if (data->processes[i][0] != '\0')
		{
			if (push_package(&data->head, data->processes[i], builtin, data))
				return (1);
		}
		current_package = data->head;
		if (data->processes[i] != NULL)
		{
			while (current_package->next)
			{
				current_package->pipe = true;
				current_package = current_package->next;
			}
		}
		i++;
	}
	return (0);
}
