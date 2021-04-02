/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:03:58 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/02 11:31:31 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_initialize_termcaps(char **term_type, int *ret)
{
	*term_type = getenv("TERM");
	if (!(*term_type))
	{
		printf("Couldn't read TERM env variable\n");
		exit(EXIT_FAILURE);
	}
	*ret = tgetent(0, term_type);
	if (*ret == 0 || *ret == -1)
	{
		printf("Tgetent returned : [%d]", ret);
		exit(EXIT_FAILURE);
	}
}
