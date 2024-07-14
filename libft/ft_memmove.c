/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:42:11 by arif              #+#    #+#             */
/*   Updated: 2023/10/24 12:10:29 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*str1;
	const unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (const unsigned char *)src;
	if (!str1 && !str2)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
		while (len--)
			*((str1 + len)) = *((str2 + len));
	return (dst);
}
