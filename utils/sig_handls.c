#include "../minishell.h"

void sig_in_cmd(int sig);
void sig_quit(int sig);

void close_herdoc(int sig)
{
	write(1, "\n", 1);
	g_exit_stat = 130;
	(void)sig;
	close(0);

}

void set_attr()
{
	struct termios termios_p;
	// fprintf(stderr, "SET_ATTR IS RUNNING\n");
	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, btn_handler);
	signal(SIGQUIT, SIG_IGN);
}

void unset_attr()
{
	struct termios termios_p;

	if (tcgetattr(1, &termios_p) == -1)
		return ;
	termios_p.c_lflag |= (ECHOCTL);
	if (tcsetattr(1, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, ft_sigchild);
	signal(SIGQUIT, sig_quit);
}

void sig_in_heredoc(int sig)
{
	if (SIGINT == sig)
	{
		set_attr();
		close(STDIN_FILENO);
		g_exit_stat = 130;
	}
	return ;
}

void	btn_handler(int sig)
{
	
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sigchild(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	sig_quit(int sig)
{
	if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}