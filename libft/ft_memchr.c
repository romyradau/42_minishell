/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:09:40 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/26 20:01:21 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	ch;

	src = (unsigned char *)s;
	ch = (char)c;
	while (n)
	{
		if (*src == ch)
			break ;
		src++;
		--n;
	}
	if (n != 0)
		return (src);
	else
		return (NULL);
}
