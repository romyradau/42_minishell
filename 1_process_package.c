#include "minishell.h"

char	*get_command(t_package **newNode, char *current)
{
	t_red	red;

	ft_bzero(&red, sizeof(t_red));
	red.left_over = ft_calloc(ft_strlen(current) + 1, sizeof(char));
	if (allocate_redirections(newNode, current) == -1)
	{
		free(red.left_over);
		return (NULL);
	}
	if (manage_red_files(newNode, current, &red) == 0)
	{
		free(red.left_over);
		return (NULL);
	}
	(*newNode)->in_redirection[red.in] = NOTHING;
	(*newNode)->out_redirection[red.out] = NOTHING;
	(*newNode)->infiles[red.in] = NULL;
	(*newNode)->outfiles[red.out] = NULL;
	return (red.left_over);
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

int	push_package(t_package **head, char *current_process, t_builtin *builtin, t_data *data)
{
	t_package	*new;
	t_package	*last;

	new = ft_calloc(sizeof(t_package), 1);
	if (new == NULL)
		return (1);
	ft_bzero(new, sizeof(t_package));
	if (fill_package(&new, current_process, builtin))
	{
		last = *head;
		if (*head == NULL)
		{
			*head = new;
			data->orig_head = *head;
			(*head)->next = NULL;
			return (0);
		}
		else
		{
			while (last->next != NULL)
				last = last->next;
			last->next = new;
			new->next = NULL;
			return (0);
		}
	}
	else
		free(new);
	return (1);
}

int	process_packages(t_data *data, t_builtin *builtin)
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
