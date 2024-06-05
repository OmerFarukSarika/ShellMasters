/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:53:33 by osarikay          #+#    #+#             */
/*   Updated: 2023/10/30 18:15:13 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	lenght;

	i = 0;
	lenght = 0;
	while (s2[lenght])
		lenght++;
	if (lenght == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i + lenght <= n)
	{
		j = 0;
		while (s2[j] && s2[j] == s1[i + j])
			j++;
		if (j == lenght)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
