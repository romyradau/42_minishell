/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:55:22 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:17:14 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	cnt1;
	size_t	cnt2;
	char	*str;

	str = (char *)b;
	cnt1 = 0;
	cnt2 = 0;
	while (cnt2 < len)
	{
		str[cnt2] = (char)c;
		cnt2++;
	}
	cnt1++;
	return (str);
}
