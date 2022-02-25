
#include "minishell.h"

void	print_package(t_package *head)
{

	int i;
	// system("clear");
	printf("===============PRINT_PACKAGE=================\n");
	while (head != NULL)
	{
	 	printf("cmd:	%s\n", head->cmd);
		// builtin_picker(head);
		 i = 0;
		   while (head->cmd_args && head->cmd_args[i])
		   {
				printf("cmd_args:	%s\n", head->cmd_args[i]);
				i++;
		   }
		 printf("pipe:	%d\n", head->pipe);
		head = head->next;
	}
	printf("===============PRINT_PACKAGE=================\n");
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


