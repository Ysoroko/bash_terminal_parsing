/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/29 12:10:15 by ysoroko          ###   ########.fr       */
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
	current_command->redirection = 0;
	if (ft_strstr(str, "<"))
		current_command->redirection = strdup("<");
	else if (ft_strstr(str, ">>"))
		current_command->redirection = strdup(">>");
	else if (ft_strstr(str, ">"))
		current_command->redirection = strdup(">");
	else if (ft_strstr(str, "|"))
		current_command->redirection = strdup("|");
	else if (ft_strstr(str, ";"))
		current_command->redirection = strdup(";");
	return ((current_command->redirection != 0));
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
	*read_so_far = malloc(sizeof(char) * (i + 1));
	if (!*read_so_far)
		exit(EXIT_FAILURE);
	ft_strlcpy(*read_so_far, input_checkpnt, i);
}

static t_command	*ft_extract_next_command(char *input_checkpnt, int *i)
{
	int			j;
	t_command	*command;
	char		*str_read_so_far;

	command = ft_new_t_command(0, 0, 0, 0);
	str_read_so_far = ft_calloc_exit(ft_strlen(input_checkpnt) + 1, 1);
	j = *i;
	while (input_checkpnt[j] && !ft_redirection_seen(str_read_so_far, command))
	{
		ft_str_read_so_far(input_checkpnt, j - *i, &str_read_so_far);
		if (!command->name && ft_command_seen(str_read_so_far))
			command->name = str_read_so_far;
		j++;
	}
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
		new_list_member = ft_lstnew_exit(command);
		ft_lstadd_back(&string_list, new_list_member);
	}
	printf("INPUT READ: [%s]\n", input);
	return (string_list);
}
