/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/29 16:15:30 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_NEW_T_COMMAND
** This function creates a new t_command structure, malloc's it and
** assigns its elements to be the arguments
** Returns the pointer to the newly created structure
*/

t_command	*ft_new_t_command(char *name, char *flags, char *arg, char *redir)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		exit(EXIT_FAILURE);
	new_command->name = name;
	new_command->flags = flags;
	new_command->argument = arg;
	new_command->redirection = redir;
	return (new_command);
}
