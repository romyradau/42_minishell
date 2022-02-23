
#include "minishell.h"

void	print_package(t_package *head)
{

	// int	flag;
	int i;
	// flag = 0;
	while (head != NULL)
	{
	 	printf("cmd:	%s\n", head->cmd);
		//  if (!flag)
		//  {
		//  	builtin_picker(head);
		//  	flag = 1;
		//  }
		 i = 0;
		  while (head->cmd_args && head->cmd_args[i])
		  {
			printf("cmd_args:	%s\n", head->cmd_args[i]);
			i++;
		  }
		printf("pipe:	%d\n", head->pipe);
		head = head->next;
	}
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
