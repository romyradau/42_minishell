#include "../minishell.h"

/**
 * SIGINT	= CTRL+C signal
*/
void	btn_handler(int sig)
{
	char	path[200];

	getcwd(path, BUFF);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(1,"",0);
	}

}
