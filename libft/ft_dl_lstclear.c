/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:32:23 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/08 17:46:19 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_DL_LSTCLEAR
** This function, given any member of t_dl_lst (double linked list) will free
** and clear all of its contents
** Unlike its t_lst equivalent, it will free in both sides (all the elements
** after, but also all the elements before the given element) and set all to 0
*/

void	ft_dl_lstclear(t_dl_lst *lst, void (*del)(void*))
{
	t_dl_lst	*temp;
	t_dl_lst	*last_address_of_temp;

	if (!lst || !del)
		return ;
	temp = lst->next;
	last_address_of_temp = temp;
	while (temp)
	{
		temp = temp->next;
		last_address_of_temp = temp;
		ft_dl_lstdelone(last_address_of_temp, del);
	}
	temp = lst;
	last_address_of_temp = temp;
	while (temp)
	{
		temp = temp->previous;
		last_address_of_temp = temp;
		ft_dl_lstdelone(last_address_of_temp, del);
	}
}
