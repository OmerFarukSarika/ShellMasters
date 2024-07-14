/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:32:09 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/07 17:24:00 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	null_free(void **alloced_name)
{
	if (alloced_name && *alloced_name)
		free(*alloced_name);
	alloced_name = NULL;
}
void	env_free(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		/* if (temp->value)
			printf("temp->value = %p\n", temp->value); */
		null_free((void *)&(temp->name));
		null_free((void *)&(temp->value));
		null_free((void *)&(temp));
	}
}

void	cmd_free(t_minishell *mini)
{
	t_cmd	*temp;

	while (mini->first_cmd)
	{
		temp = mini->first_cmd;
		mini->first_cmd = mini->first_cmd->next;
		/* if (temp->str)
			printf("temp->str = %p\n", temp->str); */
		null_free((void *)&(temp->str));
		null_free((void *)&(temp));
	}
}

void	line_free(t_minishell *mini)
{
	t_line	*temp;

	while (mini->first_line)
	{
		temp = mini->first_line;
		mini->first_line = mini->first_line->next;
		null_free((void **)&(temp->line));
		null_free((void **)&(temp));
	}
}

int	general_free(t_minishell *mini, t_mode free_type, int error_num)
{
	if (mini)
	{
		if (free_type == LINE_FREE) //! sadece o anki satır için freelenmesi gereken alanlar
		{
			if (mini->first_cmd)
				cmd_free(mini);
			//!free(mini->line);
			//?null_free((void **)&(mini->line));
			//* !!! env_list sadece program kapanırken freelenmeli !!!
		}
		else if (free_type == PROGRAM_FREE)
		{
			write(1, "PONZI\n", 7);
			cmd_free(mini);
			line_free(mini);
			//!cmd_free(mini); //! program kapatılması gerekiyorsa freelenmesi gereken alanlar. Biliyorum cmd_free için gereksiz gibi görülüyor fakat ileride burayı düzenleyeceğim. Şimdilik böyle kalsın. push swap için 3 lü freelemeyi hatırla :)
			if (mini->first_env)
				env_free(mini->first_env);
			//* merkezin freeleneceği bölüm
			//?null_free((void **)&(mini->line));
			null_free((void **)&mini);
		}
		//! tüm alanlara merkez struct olan --> mini üzerinden erişmemiz gerektiğini düşünüyoruz.	
	}
	return (ft_error(error_num));
}
/* void	general_exit(t_minishell *mini, int error_num)
{
	general_free(mini, LINE_FREE, error_num);
	ft_error(error_num);
} */

void	loop_free(char **str)
{
	while (str && *str)
	{
		free(*str);
		str++;
	}
	null_free((void **)str);
}