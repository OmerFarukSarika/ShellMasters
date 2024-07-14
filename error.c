/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor <agungor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:32:16 by osarikay          #+#    #+#             */
/*   Updated: 2024/07/06 18:35:06 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// TODO Bir tane generali exit fonksiyonu yaz ve freeledikten sonra error mesageler yazılsın.

int ft_error(int error_num)
{
    //! perror 'a dönüştürülecektir!
	if (!error_num)
		return (0);
	else if (error_num == -1)
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
	else if (error_num == -2)
		ft_putstr_fd("Error: quote error\n", 2);
    else if (error_num == -3)
        ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
    else if (error_num == -4)
        ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
    else if (error_num == -5)
        ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
    else if (error_num == -6)
        ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
    else if (error_num == -7)
        ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
    else if (error_num == -8)
        ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (error_num == -11)
		ft_putstr_fd("Error: malloc failed\n", 2);
    return (error_num);
	//! error durumlarında belki buranın işleyişi değişebilir. (exit fonksiyonunun default çıkışlarını incelemek faydalı olabilir)
}
