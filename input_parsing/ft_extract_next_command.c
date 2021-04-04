/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/04 13:33:13 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_REDIRECTION_SEEN
** This function checks if the string we're currently reading has reached
** the end of the command (which is verified by the presence of "< > >> | ;"
** inside it
** Returns 1 if we find one of these things inside (and sets t_command->redir)
** or 0 otherwise
*/

static int	ft_redirection_seen(char *str, t_command *current_command, int *j,
																char *input)
{
	if (!str)
		return (0);
	if (ft_strrchr(str, '<'))
		current_command->redirection = ft_strdup("<");
	else if (ft_strstr(str, ">>"))
		current_command->redirection = ft_strdup(">>");
	else if (ft_strrchr(str, '>'))
	{
		if (input[*j] == '>')
		{
			current_command->redirection = ft_strdup(">>");
			*j += 1;
		}
		else
			current_command->redirection = ft_strdup(">");
	}
	else if (ft_strrchr(str, '|'))
		current_command->redirection = ft_strdup("|");
	else if (ft_strrchr(str, ';'))
		current_command->redirection = ft_strdup(";");
	if (current_command->redirection)
		return (1);
	return (0);
}

/*
** FT_COMMAND_SEEN
** This function checks if the there is a command in the user's input
** we've read so far. It is only called until current t_command structure
** has a name element defined
** Returns 1 and sets the t_command->name if the command name has been seen
** Returns 0 if no command name has been seen so far
*/

static void	ft_check_if_command_seen(char *str, t_command *command, int *index)
{
	if (!command->name)
	{
		if (ft_strstr(str, "echo"))
			command->name = ft_strdup("echo");
		else if (ft_strstr(str, "cd"))
			command->name = ft_strdup("cd");
		else if (ft_strstr(str, "pwd"))
			command->name = ft_strdup("pwd");
		else if (ft_strstr(str, "export"))
			command->name = ft_strdup("export");
		else if (ft_strstr(str, "unset"))
			command->name = ft_strdup("unset");
		else if (ft_strstr(str, "env"))
			command->name = ft_strdup("env");
		else if (ft_strstr(str, "exit"))
			command->name = ft_strdup("exit");
		*index = ft_strlen(str);
	}
}

/*
** FT_CHECK_FOR_FLAGS
** The only command which can have flags for this project is "echo"
** with a flag "-n". Therefore, we are only checking if we have a "-n"
** flag while our command name is "echo". If it's the case, then
** we fill the t_command structure with the corresponding flag
*/

static void	ft_check_for_flags(char *str, t_command *command, int *index)
{
	if (!command->flags && command->name && !command->argument &&
	!ft_strcmp(command->name, "echo") && ft_strstr(str, " -n "))
	{
		command->flags = ft_strdup("-n");
		*index = ft_strlen(str);
	}
}

/*
** FT_EXTRACT_THE_ARGUMENT
** This function uses the previously saved index (which tell at which character
** of the string_read_so_far the argument starts
** (after the command name or after the flag) and it extracts the argument
** starting from that position. It removes the spaces and redirection symbol
*/

static void	ft_extract_the_argument(char *str, int index, t_command *command)
{
	command->argument = ft_strtrim_exit(&str[index],
										SPACES_AND_REDIRECTIONS);
}

/*
** FT_EXTRACT_NEXT_COMMAND
** This function analyzes the input read so far and stores it in a t_command
** structure with distinguished command, flags, argument and redirection
** It is a central hub of a transformation from input read into one separate
** t_command structure
*/

t_command	*ft_extract_next_command(char *input_checkpnt, int *i)
{
	int			j;
	t_command	*command;
	char		*str_read_so_far;
	int			index;

	command = ft_new_t_command(0, 0, 0, 0);
	str_read_so_far = 0;
	j = 0;
	while (!ft_redirection_seen(str_read_so_far, command, &j, input_checkpnt)
														 && input_checkpnt[j])
	{
		ft_update_str_read_so_far(input_checkpnt, j, &str_read_so_far);
		//printf("str_read_so_far: [%s]\n", str_read_so_far);
		ft_check_if_command_seen(str_read_so_far, command, &index);
		ft_check_for_flags(str_read_so_far, command, &index);
		j++;
	}
	ft_extract_the_argument(str_read_so_far, index, command);
	ft_free_str(str_read_so_far);
	*i += (j - 1);
	return (command);
}
