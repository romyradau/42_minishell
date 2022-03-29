#include "../minishell.h"

void	set_attr(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
	signal(SIGINT, btn_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	unset_attr(t_package *package)
{
	struct termios	termios_p;

	if (tcgetattr(1, &termios_p) == -1)
		return ;
	termios_p.c_lflag |= (ECHOCTL);
	if (tcsetattr(1, 0, &termios_p) == -1)
		return ;
	if (package->in_redirection[0] == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGQUIT, sig_quit);
	}
	signal(SIGINT, ft_sigchild);
}

void	set_termios(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, 0, &termios_p) == -1)
		return ;
}

void	sig_in_heredoc(int sig)
{
	if (SIGINT == sig)
	{
		set_attr();
		close(STDIN_FILENO);
		g_exit_stat = 130;
	}
	return ;
}
