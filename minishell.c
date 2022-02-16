//testing out readline functon

#include "minishell.h"

void	print_package(t_package *head)
{
	while (head)
	{
		printf("cmd: %s\n", head->cmd);
		printf("pipe: %d\n", head->pipe);
		head = head->next;
	}
}

void	fill_package(t_package **newNode, char *input, int operator)
{
	//functions die eine nach der anderen input-rules anwenden
	//und ein nach dem anderen package value bestücken

	(*newNode)->cmd = ft_strdup(input);
	if (operator == PIPE)
		(*newNode)->pipe = true;
	else
		(*newNode)->pipe = false;
	//wird spater gefretw ennw ir die komplette liste freen 

}

int	push_package(t_package **head, char *input, int operator)
{
	t_package *newNode;
	t_package *last;
	
	newNode = malloc(sizeof(t_package));
	if (newNode == NULL)
		return (1);
	ft_bzero(newNode, sizeof(t_package));
	fill_package(&newNode, input, operator);
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


int	char_compare(char *input, int *i)
{
	if (input[*i] == '|')
		return PIPE;
	else if (input[*i] == '<')
	{
		if (input[(*i) + 1] == '<')
		{
			(*i)++;
			return HEREDOC;
		}
		return INFILE;
	}
	else if (input[*i] == '>')
	{
		if (input[(*i) + 1] == '>')
		{
			(*i)++;
			return APPEND;
		}
		return TRUNCATE;
	}
	else
		return NOTHING;
}

void	check_metachars(char *input, t_package **head)
{
	int		i;
	int		j;
	char	*simpl_cmd;

	i = 0;
	j = 0;

	while (input[i])
	{
		int operator = char_compare(input, &i);
		if (operator || input[i + 1] == '\0')
		//++ ware (nicht wirklich aber schon )segfault | + 1 ist besser
		{
			if (operator >= 4)
			{
					simpl_cmd = ft_substr(input, j, i - 1);
					j = i + 1;
				//freen!
			}
			else
			{
				// printf("test = %c\n", input[i]);
				if (input[i + 1] == '\0')
					simpl_cmd = ft_substr(input, j, i - j + 1);
				else
					simpl_cmd = ft_substr(input, j, i - j);
				j = i + 1;
			}	
			// printf("simpl_cmd:	%s\n", simpl_cmd);
			// printf("operator:	%d\n", operator);
			// printf("symbol:	%c\n", input[i]);
			push_package(head, simpl_cmd, operator);
			free(simpl_cmd);
		}
		i++;
	}
}
int string_zerlegen(t_package **package, char *input)
{
	// char *simple_cmd;
	check_metachars(input, package);
	// check_quotes();


	// if (push_package(package, simple_cmd))
	// 	return (1);
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

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m";
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
		/* start parsing */
		string_zerlegen(package, input);

		// if (push_package(package, input))
		// 	return (1);
		/* end parsing */

		/* start execution */

		/* end execution */
		print_package(*package);
		add_history(input);
	}
	return (0);
}

int	main(int argc, char **argv, char	**env)
{
	t_package	*head;
	t_data		data;

	(void) argc;
	(void) argv;
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
