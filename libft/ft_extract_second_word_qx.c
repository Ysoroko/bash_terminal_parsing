/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_second_word_qx.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:52:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/14 15:37:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_EXTRACT_SECOND_WORD_QX
** Same es ft_extract_second_word, but will consider parts between quotes as
** being one word
** Example: ["1 2" "3 4 5 6"] with separators " " --> will extract "3 4 5 6" 
** This function extracts the second word from the "from" argument
** depending on the "separators" argument
** This is used to extract the flags in minishell
** 
*/

char	*ft_extract_second_word_qx(char *from, char *separators)
{
	int		i;
	int		j;
	char	*ret;
	char	*first_word;

	i = 0;
	j = 0;
	first_word = ft_extract_first_word_qx(from, separators);
	while (from[i] && ft_strchr(separators, from[i]))
		i++;
	while (from[i] == first_word[j] && from[i] && first_word[j])
	{
		i++;
		j++;
	}
	ret = ft_extract_first_word_qx(&(from[i]), separators);
	ft_free_str(&first_word);
	return (ret);
}
