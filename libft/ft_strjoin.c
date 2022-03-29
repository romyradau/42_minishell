/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:24:14 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:19:58 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strset(char const *s1, char *dest, unsigned int i)
{
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	return (i);
}

static char	*ft_strset_second(char const *s2, char *dest, size_t i, size_t i2)
{
	while (s2[i2] != '\0')
	{
		dest[i] = s2[i2];
		i2++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*cat_str;
	unsigned int	len;
	size_t			cnt;
	size_t			cnt2;

	if ((!s1 || !s2) || (!s1 && !s2))
		return (0);
	else
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		cat_str = (char *)malloc((len + 1) * sizeof(char));
		cnt = 0;
		cnt2 = 0;
		if (!cat_str)
			return (0);
		ft_bzero(cat_str, 0);
		cnt = ft_strset(s1, cat_str, cnt);
		return (ft_strset_second(s2, cat_str, cnt, cnt2));
	}
	return (cat_str);
}
