/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:51:18 by agungor           #+#    #+#             */
/*   Updated: 2023/10/22 03:47:58 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (s)
	{
		if (start >= str_len || !len || !str_len)
			return (ft_strdup(""));
		else if (start + len > str_len)
			len = str_len - start;
		result = (char *)malloc(len + 1);
		if (!result)
			return (NULL);
		return (ft_strlcpy(result, &s[start], len + 1), result);
	}
	return (NULL);
}
