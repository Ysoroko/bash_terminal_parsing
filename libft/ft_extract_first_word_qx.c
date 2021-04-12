/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_first_word_qx.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:33:46 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/12 15:07:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_EXTRACT_FIRST_WORD_QX
** Same as ft_extract_first_word, but only stop copying when there are no
** unclosed quotes
** Q stands for "quotes"
** X stands for "exit"
** Example: ft_extract_first_work_qx("\"          ok              \" 1 2 3")
** will extract \"          ok              \", not simply "ok"
*/

char	*ft_extract_first_word_qx(char *from, char *separators)
{
	int		i;
	int		len;
	char	*temp_copy;
	char	*ret;
	char	quote;

	i = -1;
	temp_copy = ft_strtrim_exit(from, separators);
	if (!temp_copy || !temp_copy[0])
	{
		ft_free_str(&temp_copy);
		return (0);
	}
	while (temp_copy[++i])
	{
		quote = ft_str_has_unclosed_quotes(&(temp_copy[i]));
		if (ft_strchr(separators, temp_copy[i]) && !quote)
		{
			temp_copy[i] = 0;
			break ;
		}
	}
	len = ft_strlen(temp_copy);
	if (temp_copy[len - 1] == '\"' || temp_copy[len - 1] == '\'')
		quote = temp_copy[len - 1];
	ret = ft_strxtrim_char(temp_copy, quote);
	ft_free_str(&temp_copy);
	return (ret);
}
