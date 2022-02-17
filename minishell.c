//testing out readline functon

#include "minishell.h"

void	print_package(t_package *head)
{
	while (head)
	{
		printf("cmd:	%s\n", head->cmd);
		printf("pipe:	%d\n", head->pipe);
		printf("op:	%d\n", head->redirection);

		head = head->next;
	}
}

void	print2Darray(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("pipe_package: 	%s\n", split[i]);
		i++;
	}
}

void	fill_package(t_package **newNode, char *input, int operator)
{
	//functions die eine nach der anderen input-rules anwenden
	//und ein nach dem anderen package value bestücken

	(*newNode)->cmd = ft_strdup(input);
	//freen - aber spater dann beim listen leeren
	(*newNode)->redirection = operator;
	if (operator == PIPE)
		(*newNode)->pipe = true;
	else
		(*newNode)->pipe = false;

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
		//einbauen das ab hier des danacha bgecutted wird
		//aber nur die pipe sachen abgetrennt werden!
		if (input[(*i) + 1] == '<')
		{
			(*i)++;
			// printf("input<<: 	%s\n", input);
			//function die "des danach" als package->redirection speichert
			return HEREDOC;

		}
		// printf("input<: 	%s\n", input);
		//function die "des danach" als package->redir->in speichert
		//muss aber noch als char * abgespeichert werden
		return INFILE;
	}
	else if (input[*i] == '>')
	{
		if (input[(*i) + 1] == '>')
		{
			(*i)++;
			// printf("input>>: 	%s\n", input);

			//function die "des danach" als package->redirection speichert
			return APPEND;
		}
		// printf("input>: 	%s\n", input);

		//function die "des danach" als package->redirection speichert
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
			// printf("operator:	%d\n", operator);
		if (operator || input[i + 1] == '\0')
		{
			if (operator >= 4)
			{
					simpl_cmd = ft_substr(input, j, i - j - 1);
					// printf("simpl_cmd:	%s\n", simpl_cmd);
					//des was hier steht ware schon da file!
					j = i + 1;
				//freen!
			}
			else
			{
				if (input[i + 1] == '\0')
					simpl_cmd = ft_substr(input, j, i - j + 1);
					//fur only pipes das + 1 weggemacht...
					//braucht man nur wenn da eine single pipe steht am schluss
					//ist aber invalid also besser + 1
				else
					simpl_cmd = ft_substr(input, j, i - j);
				j = i + 1;
				// printf("j:	%d\n", j);
			}	
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
	char	*input;
	char	*user;
	struct sigaction sa;

	sa.sa_handler = btn_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	user = "\e[0;36mminishell@rschleic&mjeyavat\033[0m>";
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
		char	**split = special_split(input, '|');
		if (!split)
		{
			printf("error");
			return 1;
			//nicht nur returnen sondern einfach mit nachster prompt weiter machen
		}
		// printf("split[0] = %s\n", split[0]);
		print2Darray(split);
		// (void)split;
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
