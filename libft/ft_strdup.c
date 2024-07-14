/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:46:08 by agungor           #+#    #+#             */
/*   Updated: 2023/10/22 03:45:40 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*my_strdup;

	len = ft_strlen(s1) + 1;
	my_strdup = malloc(sizeof(char) * len);
	if (my_strdup)
		ft_strlcpy(my_strdup, s1, len);
	return (my_strdup);
}
