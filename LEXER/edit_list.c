/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:35:07 by agungor           #+#    #+#             */
/*   Updated: 2024/07/13 16:35:43 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//* SILINEN NODE VERILERINI PREVE EKLEMEMIZ GEREKMEKTEDIR.
//*		çünkü	---> şöyle bir örnekte esat ' ın bilgilerini arif noduna eklemezsek "arif"esat gungor  
//*				1. tur sonucu = arifesat gungor
//*				2. tur sonucu = arifesatgungor 
//*		olmaktadır. BU DA HATALI BIR CIKTIDIR. her zaman silinen nodun bilgisini eklemeliyiz.
void	node_join_free(t_cmd	*cmd)
{
	char	*temp;
	t_cmd	*temp_node;

	temp = cmd->str;
	temp_node = cmd->next;
	printf("temp_node str = %s\n", temp_node->str);
	cmd->str = ft_strjoin(cmd->str, cmd->next->str);
	write(1, "ARIF\n", 5);
	cmd->type = cmd->next->type;
	write(1, "ARIF\n", 5);
	cmd->status = cmd->next->status;	//! status case içinde olmayabilir o yüzden buradaki önemini tam karar vermedik. fakat şuan anlaşılan silinen nodun bilgisi
	write(1, "ARIF\n", 5);
	cmd->next = cmd->next->next;
	//!printf("cmd->next->next str = %s\n", cmd->next->next->str);
	null_free((void *)&temp_node->str);
	write(1, "ARIF\n", 5);
	null_free((void *)&temp);
	write(1, "ARIF\n", 5);
	null_free((void *)&temp_node);
	write(1, "ARIF\n", 5);
}


void	edit_list(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = mini->first_cmd;
	while (cmd && cmd->next)	//* üstüne düşünüp karar vereceğiz. :)
	{
		printf("cmd->str = %s\n", cmd->str);
		printf("cmd->next->str = %s\n", cmd->next->str);
		if (cmd->type == CMD && (cmd->next->type == CMD || cmd->next->type == SPACE_CMD) && (cmd->status != NO_QUOTE || cmd->next->status != NO_QUOTE)) //! " " bilgisi önemli olabilir kafa yormamız gerekebilir ?
		{
			node_join_free(cmd);
			printf("cmd->str son hali = %s\n", cmd->str);
			cmd = mini->first_cmd;
			continue;
		}
		cmd = cmd->next;
	}
	
}