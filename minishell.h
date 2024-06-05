/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:36:06 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/05 22:33:39 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>

typedef enum e_token
{
    PIPE,
    O_QUOTE,
    D_QUOTE,
    SEMICOLON,
    O_GREATER,
    D_GREATER,
    O_LESS,
    D_LESS,

}   t_token;

typedef struct s_env
{
    struct s_env *next;
    char *name;
    char *value;
}           t_env;

typedef struct s_minishell
{
    t_env *env_list;
    char *cmd;
    char *line;
    
}   t_minishell;

# define MY_MINI_NAME "💩💩💩MINISHELL💩💩💩"

void	*s_malloc(void *name, long count, size_t size);
void    ft_error(int error_num);
void    env_list(char **env, t_minishell *mini);
void    loop_free(char **str);
t_env	*ft_lstnew_env(void *name, void *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void    generali_exit(t_minishell *mini, int error_num);
bool    check(t_minishell *mini);
char	**ft_split(char const *s);

#endif