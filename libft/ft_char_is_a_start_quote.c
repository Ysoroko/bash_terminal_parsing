/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_is_a_start_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:49:38 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/15 11:18:28 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_CHAR_IS_A_START_QUOTE
** This function will check if str[i] is a quote char and is a valid start
** of the quotes
** Returns the valid quote found or 0 if the character is not a quote
** !!! Will not check if the char is actually in the middle of other quotes
*/

char	ft_char_is_a_start_quote(char *str, int i)
{
	if ((str[i] == '\'' && i && str[i - 1] != '\\') || (str[i] == '\'' && !i))
		return ('\'');
	if ((str[i] == '\"' && i && str[i - 1] != '\\') || (str[i] == '\"' && !i))
		return ('\"');
	return (0);
}
