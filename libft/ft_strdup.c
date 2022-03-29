/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:14:41 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:19:24 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*newstr;
	unsigned long	l_str;

	l_str = ft_strlen(s1);
	newstr = (char *) ft_calloc(l_str + 1, sizeof(char));
	if (newstr == NULL)
		return (newstr);
	ft_memcpy(newstr, s1, l_str);
	return (newstr);
}
