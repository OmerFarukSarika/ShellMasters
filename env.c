/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:44:14 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/07 17:09:27 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_list(char **env, t_minishell *mini)
{
	int i;
	char **list;

	i = -1;
	while (env && env[++i])
	{
		list = ft_split(env[i], '=');
		if (list)
		{
			env_add(mini, list[0], list[1]);
			free(list);
			//!null_free((void*)&list);
			if (!list)
				write(1, "NULL DOLDU\n", 12);
		}
		else
			general_free(mini, PROGRAM_FREE, -11);
				
	}
	//!exit(0);
}