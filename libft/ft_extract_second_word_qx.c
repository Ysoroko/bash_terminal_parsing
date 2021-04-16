/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_second_word_qx.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:52:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/16 16:28:17 by ysoroko          ###   ########.fr       */
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
	char	*temp;
	char	*ret;
	char	*first_word;

	i = 0;
	first_word = ft_extract_first_word_qx(from, separators);
	//printf("first_word: [%s]\n", first_word);
	temp = ft_pos_after_the_word_in_string(from, first_word);
	if (ft_char_is_a_start_quote(temp, 0))
		i = 1;
	//printf("temp in ft_extract_sec_word: [%s]\n", &(temp[i]));
	ret = ft_extract_first_word_qx(&(temp[i]), separators);
	ft_free_str(&first_word);
	return (ret);
}
