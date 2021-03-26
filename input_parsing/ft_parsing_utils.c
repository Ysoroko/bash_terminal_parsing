/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/26 10:00:39 by ysoroko          ###   ########.fr       */
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

/*
** FT_STR_READ_SO_FAR
** This function frees the previous string read so far, malloc's a new one and 
** returns the string resulting in reading [i] characters of input
** This function is used to progressiverly read a string character by character
** and after each character extract the result as a string
** This result is later used to see if we have read a command / flag
** / argument /redirection etc
*/

void	ft_str_read_so_far(char *input, int i, char **str_read_so_far)
{
	free(*str_read_so_far);
	*str_read_so_far = malloc(sizeof(char) * (i + 1));
	if (!*str_read_so_far)
		exit(EXIT_FAILURE);
	ft_strlcpy(*str_read_so_far, input, i);
}
