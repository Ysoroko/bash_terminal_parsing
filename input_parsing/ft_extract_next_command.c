/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/22 14:08:05 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_CHECK_FOR_REDIRECTIONS
** This function checks if current_command_as_str has one of the redirection
** symbols inside of it and if so stores the corresponding redirection in 
** command->redirection element
*/

static void	ft_check_for_redirections(char *str, t_command *current_command,
										int *j, char *input)
{
	char	*redirection_found;
	char	*redir_in_input;

	//printf("str_before redirection_found: [%s]\n", str);
	if (!current_command->name)
		return ;
	redirection_found = ft_strchrset_not_quoted(str, REDIRECTIONS);
	if (!redirection_found)
		return ;
	//printf("redirection_found: [%s]\n", redirection_found);
	if (redirection_found[0] == '<')
		current_command->redirection = ft_strdup_exit("<");
	else if (redirection_found[0] == '>')
	{
		redir_in_input = ft_strchr_not_quoted(input, '>');
		if (redir_in_input[1] == '>')
			current_command->redirection = ft_strdup_exit(">>");
		else
			current_command->redirection = ft_strdup_exit(">");
	}
	current_command->redir_arg = ft_extract_first_word_qx
		(&(redir_in_input[ft_strlen(current_command->redirection)]),
			SPACES_AND_PIPES);
}

/*
** FT_EXTRACT_COMMAND_NAME
** This function extracts the first word from user's input as a command.
** It stores it in command->name element
** It modifies the *indx variable so the argument extracted afterwards
** will start extracting after the command name
*/

static void	ft_extract_command_name(char *input, t_command *command)
{
	char	*temp;

	if (!command->name)
	{
		temp = ft_extract_first_word_qx(input, SPACES_REDIRS_PIPES);
		//printf("temp: [%s]\n", temp); 
		command->name = ft_apply_quotes_and_env_vars(temp);
		if (!command->name ||
				ft_str_only_has_chars_from_charset(command->name, SPACES))
			ft_free_str(&command->name);
		ft_free_str(&temp);
		//printf("command->name: [%s]\n", command->name); 
	}
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

static void	ft_check_for_flags(char *str, t_command *command)
{
	char	*temp;

	if (!command->flags && command->name && !command->argument
		&& !ft_strcmp(command->name, "echo"))
	{
		temp = ft_extract_second_word_qx(str, SPACES);
		//printf("temp: [%s]\n", temp);
		command->flags = ft_apply_quotes_and_env_vars(temp);
		ft_free_str(&temp);
		//printf("flags: [%s]\n", command->flags);
		if (ft_strcmp(command->flags, "-n"))
			ft_free_str(&command->flags);
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

static void	ft_extract_the_argument(char *str, t_command *command)
{
	char	*index;
	char	*temp;
	char	*temp2;
	
	if (!command->name)
		return ;
	if (command->flags)
		index = ft_pos_after_the_word_in_string(str, command->flags);
	else
		index = ft_pos_after_the_word_in_string(str, command->name);
	if (index[0] == '\'' || index[0] == '\"')
		index++;
	if (!index || !index[0] || ft_strchr(PIPES, index[0]))
		return ;
	temp = ft_strdup_until_c_from_charset_not_quoted(index,
		REDIRS_AND_PIPES);
	printf("temp in extract the arg: [%s]\n", temp);
	temp2 = ft_strtrim_exit(temp, SPACES_REDIRS_PIPES);
	printf("temp2 in extract the arg: [%s]\n", temp2);
	command->argument = ft_apply_quotes_and_env_vars(temp2);
	//printf("arg: [%s]\n", command->argument);
	ft_free_str(&temp);
	ft_free_str(&temp2);
	if (command->argument && !command->argument[0])
		ft_free_str(&command->argument);
}

/*
** FT_EXTRACT_NEXT_COMMAND
** This function analyzes the input read so far and stores it in a t_command
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
	command = ft_calloc_exit(1, sizeof(t_command));
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	//printf("next_command_as_str: [%s]\n", next_command_as_str);
	j = ft_strlen(next_command_as_str);
	ft_extract_command_name(input_checkpt, command);
	ft_check_for_flags(input_checkpt, command);
	ft_check_for_redirections(next_command_as_str, command, &j, input_checkpt);
	ft_extract_the_argument(next_command_as_str, command);
	ft_check_for_pipe(next_command_as_str, command);
	ft_free_str(&next_command_as_str);
	//printf("j: [%i]\n", j);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}
