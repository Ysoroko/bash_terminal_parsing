/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_string_at_last_char.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:00:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/10 15:04:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_cut_string_at_last_char(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (str[i] == c)
			str[i] = 0;
	}
}
