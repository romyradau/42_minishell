/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_get_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:53:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/03/29 20:03:31 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	xyz(char *str, unsigned char c)
{
	int	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

void	get_exit_status(int n, int fd, t_exp *exp)
{
	char	c;

	if (n < 0)
	{
		n = n * (-1);
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n = 147483648;
		}
	}
	if (n / 10 > 0)
	{
		get_exit_status((n / 10), fd, exp);
		exp->len++;
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}
