/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:23:27 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/26 20:01:41 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			ch;
	char			*newS;

	ch = (char) c;
	newS = (char *)s;
	while (*newS != ch)
	{
		if (*newS == '\0')
			return (0);
		newS++;
	}
	return (newS);
}
