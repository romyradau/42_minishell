/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:10:34 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/18 14:23:30 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
size_t	ft_strlen(const char *s)
{
	unsigned long	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	return (cnt);
}
