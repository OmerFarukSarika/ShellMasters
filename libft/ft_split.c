/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:46:11 by agungor           #+#    #+#             */
/*   Updated: 2023/10/22 03:45:09 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_del(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	int		flag;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else if (flag)
		{
			flag = 0;
			count++;
		}
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result_string;
	size_t	word_count;
	size_t	i;

	word_count = ft_word_count(s, c);
	result_string = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result_string)
		return (0);
	i = 0;
	while (i < word_count)
	{
		if (*s != c)
		{
			result_string[i] = ft_substr(s, 0, ft_strchr(s, c) - s);
			if (!result_string[i])
				return (ft_del(result_string));
			i++;
			s = ft_strchr(s, c);
		}
		else
			s++;
	}
	result_string[i] = NULL;
	return (result_string);
}
