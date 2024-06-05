/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:32:09 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/01 18:47:16 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void list_free(void *str)
{
	(void)str;
}

void null_free(void *str)
{
    if (str)
        free(str);
    str = NULL;
}

void    loop_free(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		null_free(str[i]);
	null_free(str);
}

void    generali_exit(t_minishell *mini, int error_num)
{
    if (mini)
    {
		if (mini->env_list)
        	list_free(mini->env_list);
        null_free(mini);
    }
	ft_error(error_num);
}
