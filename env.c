/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:44:14 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/01 20:29:24 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_list(char **env, t_minishell *mini)
{
    int i;
    char **list;
    t_env *head;

    i = -1;
    mini->env_list = s_malloc(mini, 1, sizeof(t_env));
    head = mini->env_list;
    while (env[++i] && env)
    {
        list = ft_split(env[i], '=');
        mini->env_list = ft_lstnew_env(list[0], list[1]);
        mini->env_list->next = s_malloc(mini, 1000, sizeof(mini->env_list));
        printf("%s=%s\n", mini->env_list->name, mini->env_list->value);
        mini->env_list = mini->env_list->next;
        loop_free(list);
    }
    mini->env_list = head;
    while (mini->env_list->next)
    {
        printf("%s=%s\n", mini->env_list->name, mini->env_list->value);
        mini->env_list = mini->env_list->next;
    }
}