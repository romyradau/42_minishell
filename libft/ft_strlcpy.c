/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:45:24 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/26 20:02:12 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long	cnt;

	cnt = 0;
	if ((dst == NULL) || (src == NULL))
		return (0);
	if (dstsize == 0)
		return (ft_strlen (src));
	while ((src[cnt] != '\0') && (cnt < dstsize - 1))
	{
		dst[cnt] = src[cnt];
		cnt++;
	}
	dst[cnt] = '\0';
	return ((size_t)ft_strlen(src));
}
