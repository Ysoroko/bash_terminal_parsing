/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/26 13:48:05 by ysoroko          ###   ########.fr       */
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

static t_command	*ft_extract_next_command(char *input_checkpoint, int *i)
{
	int			j;
	t_command	*next_command;
	char		*string_read_so_far;

	next_command = ft_new_t_command(0, 0, 0, 0);
	string_read_so_far = ft_calloc(ft_strlen(input_checkpoint) + 1, 1);
	if (!(string_read_so_far))
		exit(EXIT_FAILURE);
	j = *i;
	while (input_checkpoint[j] && !ft_redirection_seen(string_read_so_far))
	{
		ft_str_read_so_far(input_checkpoint, j - *i, &string_read_so_far);
		if (!next_command->name && ft_command_seen(string_read_so_far))
			next_command->name = string_read_so_far;
		j++;
	}
	*i = j;
	return (ft_strdup(next_command));
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

	string_list = ft_lstnew(0);
	if (!string_list)
		exit(EXIT_FAILURE);
	i = -1;
	start_index = 0;
	while (input[++i])
	{
		command = ft_extract_next_command(&input[i], &i);
		new_list_member = ft_lstnew(command);
		if (!new_list_member)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&string_list, new_list_member);
	}
	printf("INPUT READ: [%s]\n", input);
	return (string_list);
}
