/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/30 12:43:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_INPUT_PARSING
** Central hub of parsing
** Analyzes user's input to check what functions need to be called
**
** echo [-n] [str]
** cd [str] ..... (everything after the 1st argument string is neglected)
** pwd ..... (everything after pwd is discarded)
** export [arg] .....
** unset [arg] .....
** env .... (everything after env is discarded)
** exit .... (everything after)
**
** SOLUTION
** chained list with every string separated by [; ' " > < >>]
*/

/*
** FT_REDIRECTION_SEEN
** This function checks if the string we're currently reading has reached
** the end of the command (which is verified by the presence of "< > >> | ;"
** inside it
** Returns 1 if we find one of these things inside
** or 0
*/

static int	ft_redirection_seen(char *str, t_command *current_command)
{
	if (ft_strrchr(str, '<'))
		current_command->redirection = ft_strdup("<");
	else if (ft_strstr(str, ">>"))
		current_command->redirection = ft_strdup(">>");
	else if (ft_strrchr(str, '>'))
		current_command->redirection = ft_strdup(">");
	else if (ft_strrchr(str, '|'))
		current_command->redirection = ft_strdup("|");
	else if (ft_strrchr(str, ';'))
		current_command->redirection = ft_strdup(";");
	if (current_command->redirection)
		return (1);
	return (0);
}

static int	ft_command_seen(char *str, t_command *current_command)
{
	if (ft_strstr(str, "echo"))
		current_command->name = ft_strdup("echo");
	else if (ft_strstr(str, "cd"))
		current_command->name = ft_strdup("cd");
	else if (ft_strstr(str, "pwd"))
		current_command->name = ft_strdup("pwd");
	else if (ft_strstr(str, "export"))
		current_command->name = ft_strdup("export");
	else if (ft_strstr(str, "unset"))
		current_command->name = ft_strdup("unset");
	else if (ft_strstr(str, "env"))
		current_command->name = ft_strdup("env");
	else if (ft_strstr(str, "exit"))
		current_command->name = ft_strdup("exit");
	if (current_command->name)
		return (1);
	return (0);
}

/*
** FT_STR_READ_SO_FAR
** This function frees the previous string read so far, malloc's a new one and
** returns the string resulting in reading [i] characters of input
** It is used to progressiverly read a string character by character
** and after each character extract the result as a string
** This result is later used to see if we have read a command / flag
** / argument /redirection etc
*/

static void	ft_str_read_so_far(char *input_checkpnt, int i, char **read_so_far)
{
	free(*read_so_far);
	*read_so_far = malloc(sizeof(char) * i + 1);
	if (!*read_so_far)
		exit(EXIT_FAILURE);
	ft_strlcpy(*read_so_far, input_checkpnt, i + 2);
}

/*
** FT_EXTRACT_NEXT_COMMAND
** This function analyzes the input read so far and stores it in a t_command
** structure with distinguished command, flags, argument and redirection
*/

static t_command	*ft_extract_next_command(char *input_checkpnt, int *i)
{
	int			j;
	t_command	*command;
	char		*str_read_so_far;
	int			index;

	command = ft_new_t_command(0, 0, 0, 0);
	str_read_so_far = ft_calloc_exit(ft_strlen(input_checkpnt) + 1, 1);
	j = *i;
	while (!ft_redirection_seen(str_read_so_far, command) && input_checkpnt[j])
	{
		printf("j:[%d]\n", j);
		ft_str_read_so_far(input_checkpnt, j - *i, &str_read_so_far);
		printf("READSOFAR: [%s]\n", str_read_so_far);
		if (!command->name)
		{
			ft_command_seen(str_read_so_far, command);
			index = j;
		}
		if (!command->flags && command->name && !command->argument &&
	!ft_strcmp(command->name, "echo") && ft_strstr(str_read_so_far, " -n "))
		{
			command->flags = ft_strdup("-n");
			index = j;
		}
		j++;
	}
	command->argument = ft_strtrim_exit(&str_read_so_far[index + 1],
										SPACES_AND_REDIRECTIONS);
	printf("HERE\n");
	free(str_read_so_far);
	*i = j;
	return (command);
}

/*
** FT_INPUT_PARSING
** This is the central hub of the parsing of user's input
** It uses chained lists to divide input in several separated commands which
** will be read and executed afterwards
** Returns a chained list containing every separate string from input
*/

t_list	*ft_input_parsing(char *input)
{
	t_list		*string_list;
	t_list		*new_list_member;
	int			i;
	int			start_index;
	t_command	*command;

	string_list = ft_lstnew_exit(0);
	i = -1;
	start_index = 0;
	while (input[++i])
	{
		command = ft_extract_next_command(&input[i], &i);
		printf("command adress: [%p]\n", command);
		printf("Command name: [%s]\n", command->name);
		printf("Command flag: [%s]\n", command->flags);
		printf("Command argument: [%s]\n", command->argument);
		printf("Command redirection: [%s]\n", command->redirection);
		new_list_member = ft_lstnew_exit(command);
		ft_lstadd_back(&string_list, new_list_member);
		if (!i)
			break ;
	}
	return (string_list);
}
