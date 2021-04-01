/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:12:29 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/01 09:31:25 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current_new;
	t_list	*current;

	if (!lst || !f || !del || (!(new_list = ft_lstnew(f(lst->content)))))
		return (0);
	current = lst->next;
	current_new = new_list;
	while (current != 0)
	{
		if (!(current_new = ft_lstnew(f(current->content))))
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, current_new);
		current = current->next;
	}
	return (new_list);
}
