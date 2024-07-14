/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:35:03 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/14 11:06:01 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	set_token(int c, int d)
{
	printf("c = %c | d = %c\n", c, d);
	if (c == '|')
		return (PIPE);
	else if (c == '<' && d == '<')
		return (D_LESS);
	else if (c == '<')
		return (O_LESS);
	else if (c == '>' && d == '>')
		return (D_GREATER);
	else if (c == '>')
		return (O_GREATER);
	return (MY_SPACE);
}

static void	which_qoute(t_minishell *mini)
{
	char	qoute;
	bool	type_flag;

	type_flag = true;
	qoute = mini->line[mini->end];
	if (mini->line[mini->end + 1] == qoute)
	{
		mini->end += 1;
		mini->start = mini->end + 1;
		return ;
	}
	else if (mini->line[mini->end + 1] != qoute)
	{
		while (mini->line[++mini->end] != qoute && mini->line[mini->end])
			;
		if (mini->line[mini->end + 1] == ' ')
			type_flag = false;
		mini->end--;
		mini->start++;
		if (qoute == '\'' && type_flag)
			cmd_add(mini, O_QUOTE, CMD);
		else if (qoute == '\'' && !type_flag)
			cmd_add(mini, O_QUOTE, SPACE_CMD);
		else if (qoute == '\"' && type_flag)
			cmd_add(mini, D_QUOTE, CMD);
		else if (qoute == '\"' && !type_flag)
			cmd_add(mini, D_QUOTE, SPACE_CMD);
		mini->start++;
		mini->end++;
		printf("mini->start = %d | mini->end = %d\n", mini->start, mini->end);
		printf("mini->line[mini->end] = %c\n", mini->line[mini->end]);
	}
}



static void	process_space(t_minishell *mini)
{
	if (mini->line[mini->end] != ' ')
	{
		cmd_add(mini, NO_QUOTE, set_token(mini->line[mini->end], mini->line[mini->end + 1]));
	}
	while (mini->line[mini->end] == ' ' && mini->line[mini->end + 1] == ' ')
		mini->end++;
	mini->start = mini->end + 1;
}

static void	process_redirect(t_minishell *mini, char redirect)
{
	bool	flag;

	flag = false;
	mini->end--;
	if (mini->end > mini->start)
		cmd_add(mini, NO_QUOTE, CMD);
	mini->end++;
	if (mini->line[mini->end + 1] == redirect)
	{
		mini->end++;
		flag = true;
	}
	if (!flag && redirect == '<')
		cmd_add(mini, NO_QUOTE, O_LESS);
	else if (!flag && redirect == '>')
		cmd_add(mini, NO_QUOTE, O_GREATER);
	else if (flag && redirect == '<')
		cmd_add(mini, NO_QUOTE, D_LESS);
	else if (flag && redirect == '>')
		cmd_add(mini, NO_QUOTE, D_GREATER);
}

static void	process_pipe(t_minishell *mini)
{
	if (mini->line[mini->end] == '|')
		cmd_add(mini, NO_QUOTE, PIPE);
	else
		cmd_add(mini, NO_QUOTE, CMD);
}
void	lexer(t_minishell *mini)
{
	while (mini->line && mini->line[++mini->end])
	{
		if (mini->line[mini->end] == '\'' || mini->line[mini->end] == '\"')
			which_qoute(mini);
		else if (mini->line[mini->end] == '<')
			process_redirect(mini, '<');
		else if (mini->line[mini->end] == '>')
			process_redirect(mini, '>');
		else if (mini->line[mini->end + 1] == ' ' || mini->line[mini->end] == ' ')
			process_space(mini);
		else if (mini->line[mini->end + 1] == '|' || mini->line[mini->end] == '|')
			process_pipe(mini);
		else if (mini->line[mini->end + 1] == '\0')
			cmd_add(mini, NO_QUOTE, CMD);
		else if (mini->line[mini->end + 1] == '\''
			|| mini->line[mini->end + 1] == '\"' )
		{
			cmd_add(mini, NO_QUOTE, CMD);
		}
	}
}
