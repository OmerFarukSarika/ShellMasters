/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:54:07 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/14 11:17:21 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Eğerki kapanmamış bir tırnak varsa false döndürür
static int	which_token(int token, unsigned int limit)
{
	int	error_num;

	error_num = 0;
	if (token == '<' && limit == 3)
		error_num = -3;
	else if (token == '<' && limit > 3)
		error_num = -4; // ! bash: syntax error near unexpected token `<<'
	else if (token == '|' && limit > 1)
		error_num = -5; // ! bash: syntax error near unexpected token `|'
	else if (token == '>' && limit == 3)
		error_num = -6; // ! bash: syntax error near unexpected token `>'
	else if (token == '>' && limit > 3)
		error_num = -7; // ! bash: syntax error near unexpected token `>>'
	return (error_num);
}

static int check_repeat(t_minishell *mini) {
    int i;
    char token;
    unsigned int limit;

    i = 0; // i'nin başlangıç değerini 0 olarak ayarlayın
    token = '\0';
    while (mini->line[i]) {
        limit = 0;
        if (mini->line[i] == '|' || mini->line[i] == '<' || mini->line[i] == '>') {
            token = mini->line[i];
            while (mini->line[i] == token) {
                i++;
                limit++;
            }
            if (limit >= 2) {
                write(1, "NASIL\n", 7);
                return (general_free(mini, LINE_FREE, which_token(token, limit)));
            }
        } else {
            i++; // Eğer token değilse, i'yi artırın
        }
    }
    return (0);
}


static int	check_qoute(t_minishell *mini)
{
	int		i;
	char	qoute;
	bool	flag;

	flag = false;
	i = -1;
	while (mini->line[++i])
	{
		if ((mini->line[i] == '\"' || mini->line[i] == '\'') && flag == false)
		{
			qoute = mini->line[i];
			flag = true;
		}
		else if (flag == true && mini->line[i] == qoute)
			flag = false;
	}
	if (flag)
		return (general_free(mini, LINE_FREE, -2)); //! bir hata durumu line freelenmeli exit atmamalıyız
	return (0);
}

int	general_check(t_minishell *mini)
{
	int i;

	mini->start = 0;
	mini->end = -1;
	i = -1;
	if (check_qoute(mini)) //! return durumu kaldırıldı hata oluşursa program kendisi içersinden exit atıyor.
		return (-2);
	else if (check_repeat(mini)) //* burada which_token -3,-4,..,-7 sayılarında birini return edecek fakat bizim -3 return etmemiz çok önemli değil fonksiyonun while içine girmemesi bizim için yeterli.
		return (-3);
	while(mini->line[++i]) //! burada düşünülüp yapmadığım --> <                     >  durumlarında hata vermesini parser durumunda yapacağız.
	{
		if (mini->line[i] == '<' && mini->line[i + 1] == '>')
			return(general_free(mini, LINE_FREE, -8));						//* PROGRAM_FREE olarak belirlemek büyük bir hataya yol açmaktadır. (TOKEN)ların hatalı girişlerinde LINE düzeyinde bir freeleme sisteni kurduk.
		else if (mini->line[i] == '>' && mini->line[i + 1] == '<')
			return (general_free(mini, LINE_FREE, -8));
		else if (mini->line[i] == '<' && mini->line[i + 1] == '|')
			return (general_free(mini, LINE_FREE, -5));			
	}
	return (0);
}