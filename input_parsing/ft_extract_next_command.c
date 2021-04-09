/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/09 09:53:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_REDIRECTION_SEEN
** This function checks if current_command_as_str has one of the redirection
** symbols inside of it and if so stores the corresponding redirection in 
** command->redirection element
*/

static void	ft_check_for_redirections(char *str, t_command *current_command,
										int *j, char *input)
{
	if (!str)
		return ;
	if (ft_strrchr(str, '<'))
		current_command->redirection = ft_strdup_exit("<");
	else if (ft_strrchr(str, '>'))
	{
		if (input[*j] == '>')
		{
			current_command->redirection = ft_strdup_exit(">>");
			*j += 1;
		}
		else
			current_command->redirection = ft_strdup_exit(">");
	}
	else if (ft_strrchr(str, '|'))
		current_command->redirection = ft_strdup_exit("|");
	else if (ft_strrchr(str, ';'))
		current_command->redirection = ft_strdup_exit(";");
}

/*
** FT_COMMAND_SEEN
** This function extracts the first word from user's input as a command.
** It stores it in command->name element
*/

static void	ft_extract_command_name(char *input, t_command *command, int *indx)
{
	char	*temp;

	temp = ft_strdup_until_c_from_charset(input, REDIRECTIONS);
	if (!command->name)
	{
		command->name = ft_extract_first_word(temp, SPACES_AND_REDIRECTIONS);
		*indx = ft_strlen(command->name) + 1;
		//printf("index after name: [%d]\n", *indx);
	}
	ft_free_str(&temp);
}

/*
** FT_CHECK_FOR_FLAGS
** The only command which can have flags for this project is "echo"
** with a flag "-n". Therefore, we are only checking if we have a
** flag while our command name is "echo". If it's the case, and the encountered
** flag is "-n", we fill the t_command structure with the corresponding flag
** If the flag isn't "-n", we ignore it as a flag 
** and consider it being a part of the argument
*/

static void	ft_check_for_flags(char *str, t_command *command, int *index)
{
	if (!command->flags && command->name && !command->argument
		&& !ft_strcmp(command->name, "echo"))
	{
		command->flags = ft_extract_second_word(str, SPACES);
		if (!ft_strcmp(command->flags, "-n"))
			*index = ft_strchrn(str, 'n') + 1;
		else
			ft_free_str(&command->flags);
		//printf("index after flags: [%d]\n", *index);
	}
}

/*
** FT_EXTRACT_THE_ARGUMENT
** This function uses the previously saved index (which tell at which character
** of the next_command_as_str the argument starts
** (after the command name or after the flag) and it extracts the argument
** as a string starting from that position. 
** It also removes the spaces and redirection symbols at the start and at 
** the end of the resulting string
*/

static void	ft_extract_the_argument(char *str, int index, t_command *command)
{
	if (!str[index] || ft_strchr(REDIRECTIONS, str[index]))
		return ;
	//printf("arg: [%s]\n", command->argument);
	//printf("&str[index]: [%s]\n", &str[index]);
	command->argument = ft_strtrim_exit(&(str[index]),
			SPACES_AND_REDIRECTIONS);
	//printf("arg: [%s]\n", command->argument);
	if (command->argument && !command->argument[0])
		ft_free_str(&command->argument);
}

/*
** FT_EXTRACT_NEXT_COMMAND
** This function analyzes the input read so far and stores it in a t_command
** structure with distinguished command, flags, argument and redirection
** It is a central hub of a transformation from input read into one separate
** t_command structure
*/

t_command	*ft_extract_next_command(char *input_checkpt, int *i)
{
	int			j;
	t_command	*command;
	char		*next_command_as_str;
	int			index;

	index = 0;
	command = ft_new_t_command(0, 0, 0, 0);
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	//printf("next_command_as_str: [%s]\n", next_command_as_str);
	if (!next_command_as_str)
		return (command);
	j = ft_strlen(next_command_as_str);
	ft_extract_command_name(input_checkpt, command, &index);
	ft_check_for_flags(input_checkpt, command, &index);
	ft_check_for_redirections(next_command_as_str, command, &j, input_checkpt);
	ft_extract_the_argument(next_command_as_str, index, command);
	ft_free_str(&next_command_as_str);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}
