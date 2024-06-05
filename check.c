/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:54:07 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/05 21:41:55 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strcpy(char *s1, char *s2)
{
    int i;
 
    i = 0;
    while (s2[i])
    {
        s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
        i++;
    }
    s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
    return (s1);
}


// ! Eğerki kapanmamış bir tırnak varsa false döndürür

bool    check(t_minishell *mini)
{
    int i;
    char qoute;
    bool flag = false;

    i = -1;
    while (mini->line[++i])
    {
        if ((mini->line[i] == '\"' || mini->line[i] == '\'') && flag == false)
        {
            qoute = mini->line[i];
            flag = true;
        }
        else if (mini->line[i] == qoute && flag == true)
            flag = false;   
    }
    return (!flag);
}