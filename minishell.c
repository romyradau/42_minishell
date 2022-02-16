//testing out readline functon

#include "minishell.h"

void	print_package(t_package *head)
{
	while (head)
	{
		printf("prompt: %s\n", head->cmd);
		head = head->next;
	}
}

void	fill_package(t_package **newNode, char *input)
{
	//functions die eine nach der anderen input-rules anwenden
	//und ein nach dem anderen package value bestücken
	(*newNode)->cmd = input;

}

int	push_package(t_package **head, char *input)
{
	t_package *newNode;
	t_package *last;
	
	newNode = malloc(sizeof(t_package));
	if (newNode == NULL)
		return (1);
	ft_bzero(newNode, sizeof(t_package));
	fill_package(&newNode, input);
	last = *head;
	if (*head == NULL)
	{
		*head = newNode;
		(*head)->next = NULL;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	//zeile die neue node dran hängt
	newNode->next = NULL;
	return (0);
}

int	prompt(t_package **package)
{
	// char	path[200];
	char	*input;
	char	*user;
	struct sigaction sa;

	sa.sa_handler = btn_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
	// getcwd(path, BUFF);
	while (1)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (-1);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (-1);
		input = readline(user);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			return (1);
		}
		if (push_package(package, input))
			return (1);
		print_package(*package);
		add_history(input);
	}
	return (0);
}

int	main(char	**env)
{
	t_package	*head;
	t_data		data;

	data.env = env;
	//env in data.env speichern
	head = NULL;
	
	if (prompt(&head))
	{
		//free
		//correct error message
		return(1);
	}
	return (0);
}
