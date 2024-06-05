/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:42:24 by osarikay          #+#    #+#             */
/*   Updated: 2023/10/30 16:27:28 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	lenght;
	size_t	i;
	size_t	j;

	lenght = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	string = (char *)malloc(lenght + 1);
	if (string == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		string[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
	{
		string[j] = s2[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}
