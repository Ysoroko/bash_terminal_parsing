/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:03:58 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/01 14:07:04 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_initialize_termcaps(char **term_type, int *ret)
{
	*term_type = getenv("TERM");
	if (!(*term_type))
		exit(EXIT_FAILURE);
	*ret = tgetent(0, term_type);
	if (*ret == 0 || *ret == -1)
		exit(EXIT_FAILURE);
}