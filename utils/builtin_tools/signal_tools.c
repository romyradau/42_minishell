/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:48:40 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 22:48:41 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	close_herdoc(int sig)
{
	write(1, "\n", 1);
	g_exit_stat = 130;
	(void)sig;
	close(0);
}
