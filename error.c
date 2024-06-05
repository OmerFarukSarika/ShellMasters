/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay < osarikay@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:32:16 by osarikay          #+#    #+#             */
/*   Updated: 2024/06/01 17:11:28 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

// TODO Bir tane generali exit fonksiyonu yaz ve freeledikten sonra error mesageler yazılsın.

void ft_error(int error_num)
{
    if (error_num == -1)
        ft_putstr_fd("Error: wrong number of arguments\n", 2);
    if (error_num == -11)
        ft_putstr_fd("Error: malloc failed\n", 2);
    exit(error_num * -1);
}