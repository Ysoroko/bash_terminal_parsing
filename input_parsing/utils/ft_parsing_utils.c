/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/04 15:14:57 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (command->result)
		ft_free_str(&(command->result));
	if (command->redir_arg)
		ft_free_str(&(command->redir_arg));
	free(command_pointer);
	command_pointer = 0;
}

/*
** FT_EXTRACT_NEXT_COMMAND_STRING
** This function will create a malloc'd duplicate of inupt_checkpoint
** argument, ending at the first redirection character
*/

char	*ft_extract_next_command_string(char *checkpoint)
{
	char	*ret;

	ret = ft_strdup_until_c_from_charset_not_quoted(checkpoint, PIPES);
	if (ft_str_only_has_chars_from_charset(ret, SPACES))
		ft_free_str(&ret);
	return (ret);
}

/*
** FT_CHECK_FOR_PIPE
** This functions checks if we have a redirection char in str_command
** argument and stores it in t_command "pipe" element
*/

void	ft_check_for_pipe(char *str_command, t_command *command)
{
	int	len;

	if (!str_command || !command)
		return ;
	len = ft_strlen(str_command);
	if (str_command[len - 1] == '|' || str_command[len - 1] == ';')
		command->pipe = str_command[len - 1];
}
