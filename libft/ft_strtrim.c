/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:34:16 by agungor           #+#    #+#             */
/*   Updated: 2023/10/22 03:47:36 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*start;
	char	*result;
	size_t	len;

	start = (char *)s1;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (*start && ft_strchr(set, *start))
		start++;
	while (end >= start && ft_strchr(set, *end))
		end--;
	len = end - start + 2;
	result = (char *)malloc(len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len);
	return (result);
}
