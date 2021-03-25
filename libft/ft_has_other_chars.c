/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_other_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:21:10 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/22 14:46:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_has_other_chars(char *str, const char *allowed_charset)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(allowed_charset, str[i]))
			return (1);
	}
	return (0);
}