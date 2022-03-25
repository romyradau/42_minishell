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
	(*newNode)->in_redirection[red.iR] = NOTHING;
	(*newNode)->out_redirection[red.oR] = NOTHING;
	(*newNode)->infiles[red.iR] = NULL;
	(*newNode)->outfiles[red.oR] = NULL;
	return (red.left_over);
}

int	fill_package(t_package **new, char *current_process, t_builtin *builtin)
{
	char	*full_cmd;

	full_cmd = ft_strtrim(get_command(new, current_process), " ");
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

int	push_package(t_package **head, char *current_process, t_builtin *builtin)
{
	t_package	*new;
	t_package	*last;

	new = malloc(sizeof(t_package));
	if (new == NULL)
		return (1);
	ft_bzero(new, sizeof(t_package));
	if (fill_package(&new, current_process, builtin))
	{
		last = *head;
		if (*head == NULL)
		{
			*head = new;
			(*head)->next = NULL;
			return (0);
		}
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
		return (0);
	}
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
			if (push_package(&data->head, data->processes[i], builtin))
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
