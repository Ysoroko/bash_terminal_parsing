/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_between_the_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:46:30 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/10 17:04:53 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	ft_char_between_the_quotes(int char_position, char *str_containing_c)
{
	char	*temp;
	char	quote;

	temp = ft_strldup_exit(str_containing_c, char_position + 1);
	quote = ft_str_has_unclosed_quotes(temp);
	ft_free_str(&temp);
	return (quote);
}
