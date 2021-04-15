/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_between_the_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:46:30 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/15 11:19:26 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_CHAR_BETWEEN_THE_QUOTES
** This function will check if the character str_containing_c[char_position]
** is included between quotes (single or double) and return
** the corresponding quote or '\0' if the character is not between the quotes
*/

char	ft_char_between_the_quotes(int c_pos, char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i] && i <= c_pos)
	{
		quote = ft_char_is_a_start_quote(str, i);
		if (quote)
		{
			while (str[i] && i <= c_pos)
			{
				if (ft_char_is_a_start_quote(str, i) == quote)
				{
					quote = 0;
					break ;
				}	
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (quote);
}
