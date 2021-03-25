/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:57:11 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 14:59:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_DISPLAY_PROMPT
** This function is used to display the prompt name on STDOUT in the specified
** color
*/

void	ft_display_prompt(char *color, char *prompt_name)
{
	write(1, color, 10);
	write(1, prompt_name, (int)ft_strlen(prompt_name));
	write(1, "\x1b[0m", 5);
}
