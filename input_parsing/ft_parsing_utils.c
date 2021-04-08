/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/08 15:21:45 by ysoroko          ###   ########.fr       */
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
	new_command->prev_command = 0;
	return (new_command);
}

/*
** FT_FREE_T_COMMAND
** This function is used to free the t_command structure's elements,
** set al of them to NULL pointers using ft_free_str to avoid double free
** and then free and set t_command to NULL itself
*/

void	ft_free_t_command(void *command_pointer)
{
	t_command	*command;

	if (!command_pointer)
		return ;
	command = (t_command *)(command_pointer);
	if (command->name)
		ft_free_str(&(command->name));
	if (command->flags)
		ft_free_str(&(command->flags));
	if (command->argument)
		ft_free_str(&(command->argument));
	if (command->redirection)
		ft_free_str(&(command->redirection));
	free(command_pointer);
	command_pointer = 0;
}

/*
** FT_EXTRACT_NEXT_COMMAND_STRING
** This function will create a malloc'd duplicate of inupt_checkpoint
** argument, ending at the first redirection character
*/

char	*ft_extract_next_command_string(char *input_checkpoint)
{
	char	*ret;

	ret = ft_strdup_until_c_from_charset(input_checkpoint, REDIRECTIONS);
	if (ft_str_only_has_chars_from_charset(ret, SPACES))
		ft_free_str(&ret);
	return (ret);
}
