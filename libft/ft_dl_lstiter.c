/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:39:41 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/08 17:42:29 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_DL_LSTITER
** Unlike its t_lst equivalent, it will apply function f to all of the element
** before and after the *lst element
*/

void	ft_dl_lstiter(t_dl_lst *lst, void (*f)(void *))
{
	t_dl_lst	*temp;

	if (!lst || !f)
		return ;
	temp = lst->next;
	while (temp != 0)
	{
		f(temp->content);
		temp = temp->next;
	}
	temp = lst;
	while (temp != 0)
	{
		f(temp->content);
		temp = temp->previous;
	}
}
