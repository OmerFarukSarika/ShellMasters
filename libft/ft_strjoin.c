/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:27:33 by agungor           #+#    #+#             */
/*   Updated: 2023/10/22 03:46:04 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*my_strjoin;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	my_strjoin = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!(my_strjoin))
		return (NULL);
	ft_memcpy(my_strjoin, s1, len1);
	ft_memcpy(my_strjoin + len1, s2, len2);
	my_strjoin[len1 + len2] = '\0';
	return (my_strjoin);
}
