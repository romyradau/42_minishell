#include "../minishell.h"

/**
 * SIGINT	= CTRL+C signal
*/

void sig_in_cmd(int sig);
void sig_quit(int sig);

void close_herdoc(int sig)
{
	write(1, "\n", 1);
	g_exit_stat = 130;
	(void)sig;
	close(0);

}

int prep_signal(t_data *data)
{
	data->sa.sa_handler = sig_in_cmd;
	if (sigaction(SIGINT, NULL, &data->sa) == -1)
		return (-1);
	data->cntrl_backslasch.sa_handler = sig_quit;
	if (sigaction(SIGQUIT, &data->cntrl_backslasch, NULL) == -1)
		return (-1);
	return (0);
}

void sig_in_cmd(int sig)
{
	write(1, "\n", 1);
	g_exit_stat = 130;
	(void) sig;
}

void	btn_handler(int sig)
{

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_quit(int sig)
{
	write(2, "Quit: 3\n", 8);
	g_exit_stat = 131;
	(void) sig;
}