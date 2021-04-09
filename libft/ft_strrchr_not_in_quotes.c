/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_not_in_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:27:27 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/09 11:56:23 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_PASS_QUOTES
** This function is used to ignore the parts of the string with between the
** quotes (both simple and double)
** It will decrement the *index until it sees that the open quote (simple or 
** double) was closed or we have reached the start
*/

static	void	ft_pass_quotes(char *str, int *index)
{
	char	until_this_quote_is_closed;

	until_this_quote_is_closed = 0;
	if (*index)
	{
		if (str[*index] == '\'' && str[*index - 1] != '\\')
			until_this_quote_is_closed = '\'';
		else if (str[*index] == '\"' && str[*index - 1] != '\\')
			until_this_quote_is_closed = '\"';
		if (until_this_quote_is_closed)
		{
			while ((*index > 0 && str[*index] != until_this_quote_is_closed)
				|| (*index > 0 && str[*index] == until_this_quote_is_closed
					&& str[*index - 1] == '\\'))
				(*index)--;
		}
	}
}

/*
** FT_STRRCHR_NOT_IN_QUOTES
** Same as ft_strrchr (looking for a char's adress starting at the end of the
** string), but this function will ignore all of the chars enclosed in
** simple or double quotes
** ! If the string has some unclosed quotes, it will return NULL
** If it doesn't find the character c in the string, it will also return NULL
** Otherwise, the pointer to the last occurence of character c in the string
** is returned
*/

char	*ft_strrchr_not_in_quotes(char *str, char c)
{
	int	str_len;
	int	in_quotes;

	if (!str || ft_str_has_unclosed_quotes(str))
		return (0);
	in_quotes = 0;
	str_len = ft_strlen(str);
	if (!c)
		return (&str[str_len]);
	while (str_len > 0)
	{
		ft_pass_quotes(str, &str_len);
		if (str[str_len] == c)
			return (&str[str_len]);
		str_len--;
	}
	return (0);
}
