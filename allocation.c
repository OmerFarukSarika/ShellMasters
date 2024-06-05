/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:47:07 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/01 19:38:53 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*s_malloc(void *name, long count, size_t size)
{
	void	*result;
    
    (void)name;
	result = NULL;
	result = ft_calloc(count, size);
	if (!result)
		generali_exit(name, -11);
	return (result);
}

t_env	*ft_lstnew_env(void *name, void *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
    new->name = name;
	new->value = value;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}