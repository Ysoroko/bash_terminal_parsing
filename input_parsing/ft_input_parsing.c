/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/06 17:32:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_INPUT_PARSING
** This is the central hub of the parsing of user's input
** It uses chained lists to divide input in several separated commands which
** will be read and executed afterwards
** Returns a chained list with pointers to each command's name / flags /
** arguments / redirections
*/

t_list	*ft_input_parsing(char *input)
{
	t_list		*command_list;
	t_list		*new_list_member;
	int			i;
	t_command	*command;

	command_list = ft_lstnew_exit(0);
	i = -1;
	while (input[++i])
	{
		command = ft_extract_next_command(&input[i], &i);
		if (!command_list->content)
			command_list->content = command;
		else
		{
			new_list_member = ft_lstnew_exit((void *)command);
			ft_lstadd_back(&command_list, new_list_member);
		}
		if (!input[i])
			break ;
	}
	return (command_list);
}
