
#include "minishell.h"

void	print_package(t_package *head, t_builtin *builtin)
{
	(void)builtin;
	int x;
	// system("clear");
	printf("\n\n===============PRINT_PACKAGE START=================\n\n");
	while (head != NULL)
	{
	 	printf("cmd:		%s\n", head->cmd);
		x = 0;
		while (head->cmd_args && head->cmd_args[x])
		{
				printf("cmd_args:		%s\n", head->cmd_args[x]);
				x++;
		}
		for (int i = 0; head->out_redirection[i] != 0; i++)
			printf("out_redirection[%d]:	%d\n", i , head->out_redirection[i]);
		for (int i = 0; head->in_redirection[i] != 0; i++)
			printf("in_redirection[%d]:	%d\n", i , head->in_redirection[i]);
		for	(int i = 0; head->infiles[i] != NULL; i++)
			printf("infiles[%d]:		%s\n", i , head->infiles[i]);
		for	(int i = 0; head->outfiles[i] != NULL; i++)
			printf("outfiles[%d]:		%s\n", i , head->outfiles[i]);
		printf("pipe:	%d\n\n\n", head->pipe);
		head = head->next;
	}
	// builtin_picker(head, builtin);
	printf("===============PRINT_PACKAGE END=================\n\n");
}

void	print2Darray(char **split)
{
	int	i;

	i = 0;
	printf("-------- pipe_package start --------\n");
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	printf("-------- pipe_package end --------\n\n");
}


