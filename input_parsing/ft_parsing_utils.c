/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/04 17:00:07 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_STR_READ_SO_FAR
** This function frees the previous string read so far, malloc's a new one and
** returns the string resulting in reading [i] characters of input
** It is used to progressiverly read a string character by character
** and after each character extract the result as a string
** This result is later used to see if we have read a command / flag
** / argument /redirection etc
*/

void	ft_update_str_read_so_far(char *input_checkpnt, int i, char **prev)
{
	int	to_copy;

	if (!i)
		to_copy = 1;
	else
		to_copy = i + 1;
	ft_free_str(prev);
	*prev = malloc(sizeof(char) * (to_copy + 1));
	if (!(*prev))
		exit(EXIT_FAILURE);
	ft_strlcpy(*prev, input_checkpnt, to_copy + 1);
}

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
