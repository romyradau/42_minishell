#include "minishell.h"

void	free_redirections(t_package	*tmp)
{
	int	i;

	i = 0;
	while (tmp->infiles && tmp->infiles[i] != NULL)
	{
		free(tmp->infiles[i]);
		i++;
	}
	if (tmp->in_redirection)
		free(tmp->in_redirection);
	if (tmp->infiles)
		free(tmp->infiles);
	i = 0;
	while (tmp->outfiles && tmp->outfiles[i] != NULL
		&& tmp->outfiles[i][0] != '\0')
	{
		free(tmp->outfiles[i]);
		i++;
	}
	if (tmp->out_redirection)
		free(tmp->out_redirection);
	if (tmp->outfiles)
		free(tmp->outfiles);
}

void	free_packages(t_data *data)
{
	t_package	*tmp;
	int			i;

	i = 0;
	while (data->head != NULL)
	{
		tmp = data->head;
		while (tmp->cmd_args && tmp->cmd_args[i] != NULL)
		{
			free(tmp->cmd_args[i]);
			i++;
		}
		if (tmp->cmd_args)
			free(tmp->cmd_args);
		free_redirections(tmp);
		free(tmp);
		data->head = data->head->next;
	}
}