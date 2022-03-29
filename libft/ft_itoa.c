/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:35:03 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/03/29 23:15:02 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_lenght(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = n * (-1);
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_settonegativ(char *result, int f)
{
	if (f)
	{
		result[0] = '-';
		return (result);
	}
	else
		return (result);
}

static char	*ft_fill(char *result, int len, int n)
{
	while (len > 0)
	{
		result[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		f;

	f = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = number_lenght(n);
	if (n < 0)
	{
		f = 1;
		n = -n;
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (result);
	result[len] = '\0';
	result = ft_fill(result, len, n);
	return (ft_settonegativ(result, f));
}
