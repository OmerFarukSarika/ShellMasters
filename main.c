/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:21:42 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/05 22:32:05 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac, (void)av, (void)env;
    t_minishell *mini;

    if (ac != 1)
        ft_error(-1);
    mini = s_malloc(NULL, 1, sizeof(t_minishell));
    env_list(env, mini);
    exit(0);
    while (1)
    {
        mini->line = readline(MY_MINI_NAME);
        if (check(mini))
        {
            //parse(mini);
            //execute(mini);
            printf("PONZİ\n");
            printf("%s\n", mini->line);
            free(mini->line);
        }
        else
        {
            printf("Error: unclosed quote\n");
            free(mini->line);
        }
    }
}