/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_not_quoted.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:41:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/10 17:06:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_STRCHR_NOT_QUOTED
** Same as ft_strchr, but the character we're looking for must not be between 
** two quotes (simple or double). If the function reads a character it is
** looking for between two quotes, it will ignore it and keep looking
*/

char	*ft_strchr_not_quoted(const char *str, int c)
{
	int		i;
	char	*my_str;

	my_str = (char *)(str);
	i = 0;
	while (my_str[i])
	{
		if (my_str[i] == c && !ft_char_between_the_quotes(i, my_str))
			return (&my_str[i]);
		i++;
	}
	if (my_str[i] == c)
		return (&my_str[i]);
	return (0);
}
