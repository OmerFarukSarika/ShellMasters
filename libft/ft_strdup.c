/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:00:00 by osarikay          #+#    #+#             */
/*   Updated: 2023/10/30 18:06:27 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	lenght;
	char	*str;

	lenght = ft_strlen(s1);
	str = (char *)malloc(lenght + 1);
	if (str != NULL)
	{
		ft_memcpy(str, s1, lenght + 1);
	}
	return (str);
}
