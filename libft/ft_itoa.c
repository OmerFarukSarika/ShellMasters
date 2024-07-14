/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:17:50 by agungor           #+#    #+#             */
/*   Updated: 2023/10/24 12:01:23 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	number_length(int c)
{
	size_t	len;

	len = 1;
	if (c <= 0)
	{
		len++;
		c *= -1;
	}
	while (c && ++len)
		c /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*string_num;
	long	number;

	number = n;
	len = number_length(n);
	string_num = (char *)malloc(len);
	if (!string_num)
		return (NULL);
	if (n < 0)
	{
		string_num[0] = '-';
		number *= -1;
	}
	if (!n)
		string_num[0] = '0';
	string_num[--len] = '\0';
	while (number)
	{
		string_num[--len] = number % 10 + 48;
		number /= 10;
	}
	return (string_num);
}
