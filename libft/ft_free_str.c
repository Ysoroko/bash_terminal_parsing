/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:31:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/30 16:32:21 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_FREE_STR
** This function frees its argument and sets its pointer to NULL to avoid
** double free in the future
*/

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = 0;
	}
}