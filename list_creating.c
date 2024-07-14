/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:03:56 by agungor           #+#    #+#             */
/*   Updated: 2024/07/12 19:13:14 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	string_selection(t_minishell *mini, t_cmd *new)
{
	int	i;
	int	j;

	j = -1;
	i = mini->start - 1;
	new->str = s_malloc(mini, mini->end - mini->start + 2, sizeof(char));
	while (++i <= mini->end)
		new->str[++j] = mini->line[i];
	new->str[++j] = '\0';
	/*
		* burada listenin elemanlarının boyutlarına bakarak boşlukların cmd ye sızıp sızmadığını anladık
		!if (new->str[0] == 'e')
		!	printf("****> %zu\n", ft_strlen(new->str));
		!else if (new->str[0] == ' ')
		!	printf("----> %zu\n", ft_strlen(new->str));
	*/
}

void	cmd_add(t_minishell *mini, t_status status, t_token type)
{
	t_cmd	*new;

	//!printf("cmd addtek ----> start = %d   end = %d\n", mini->start, mini->end);
	new = s_malloc(mini, 1, sizeof(t_cmd));
	string_selection(mini, new);
	new->status = status;
	new->type = type;
	new->next = NULL;
	if (!mini->first_cmd)
		mini->first_cmd = new;
	else
		mini->last_cmd->next = new;		//! listeyi bağlamak için
		//mini->last_cmd = new;       	//! listenin son elemanını göstermek için
	mini->last_cmd = new;				//! her case içerisinde yapıldığı için buraya taşıdım.
	mini->start = mini->end + 1;
}

/* void	normalize_quotes(t_minishell *mini)
{
	int 	start;
	char 	*temp;
	char	qoute;

	start = 0;
	qoute = '\0';
	temp = NULL;
	while (mini->line[mini->end] && !is_token(mini->line[mini->end + 1]))
	{
		printf("quote = %c\n", qoute);
		printf("end = %d | mini->line[mini->end] = %c\n", mini->end, mini->line[mini->end]);
		if (mini->line[mini->end] == '\"' || mini->line[mini->end] == '\'')
		{
			qoute = mini->line[mini->end];
			mini->end++;
			start = mini->end;
		}
		temp = mini->last_cmd->str;
		while (mini->line[mini->end] && mini->line[mini->end + 1] != qoute)
		{
			if (is_token(mini->line[mini->end + 1]))
			{
				mini->start = mini->end + 1;
				break ;
			}
			mini->end++;
		}
		printf("start = %d | mini->end = %d\n", start, mini->end);
		mini->last_cmd->str = ft_strjoin(mini->last_cmd->str, start_end_cpy(mini, mini->line, start, mini->end));
		null_free((void *)&temp);
	}
	printf("CIKIS -->mini->line[mini->end] = %c\n", mini->line[mini->end]);
	
} */

void	env_add(t_minishell *mini, char *name, char *value)
{
	t_env	*new;

	new = s_malloc(mini, 1, sizeof(t_env)); //! 1. parametre NULL'du
	new->name = name;
	new->value = value;
	new->next = NULL; // calloc üzerince açtığımız için define'ı NULL olarak gelmektedir.
	if (!mini->first_env)
		mini->first_env = new;
	else
		mini->last_env->next = new;
	mini->last_env = new; //! her case içerisinde yapıldığı için buraya taşıdım.
}

void	line_add(t_minishell *mini)
{
	t_line	*new;
	
	new = s_malloc(mini, 1, sizeof(t_line));
	new->line = mini->line;
	//new->next = NULL; //! ft_calloc kullandığım için gerek kalmayabilir ? ilerde pushlamaya yakın silip check edebiliriz
	if (!mini->first_line)
		mini->first_line = new;
	else
		mini->last_line->next = new;
	mini->last_line = new;
}

/*
	line = ome"r"|arif

	cmd = ome
	cmd = r	status D_QUOTE
	cmd = |
	cmd = arif */