/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset_not_quoted.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:42:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/12 17:43:13 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** Same as ft_strchr, but instead of looking for only one character,
** is looking for one of the characters of the charset.
** Also it only considers a character to be found if it's not between two
** quotes (single or double)
** Returns the address of the first occurence of one of the charset characters
** or a NULL pointer if none were found
*/

char	*ft_strchrset_not_quoted(char *str, char *charset)
{
	int		i;
	char	*found;

	if (!str || !charset)
		return (0);
	i = -1;
	while (str[++i])
	{
		found = ft_strchr_not_quoted(charset, str[i]);
		if (found)
			return (found);
	}
	return (0);
}
