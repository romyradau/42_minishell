/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:50:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:20:36 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	index;

	index = 0;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	sub = (char *)ft_calloc((len + 1), sizeof(char));
	if (sub == 0)
		return (0);
	while ((s[start] != '\0') && (index < len))
	{
		sub[index] = s[start];
		index++;
		start++;
	}
	sub[index] = '\0';
	return (sub);
}
