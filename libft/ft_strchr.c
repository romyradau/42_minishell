/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:23:27 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:18:41 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			ch;
	char			*new_s;

	ch = (char) c;
	new_s = (char *)s;
	while (*new_s != ch)
	{
		if (*new_s == '\0')
			return (0);
		new_s++;
	}
	return (new_s);
}
