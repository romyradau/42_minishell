/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:26:37 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:16:26 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	if ((dst == 0) && (src == 0))
		return (0);
	while (n)
	{
		*(tmp_dst++) = *(tmp_src++);
		--n;
	}
	return (dst);
}
