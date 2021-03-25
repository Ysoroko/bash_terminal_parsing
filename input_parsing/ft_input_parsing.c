/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 17:43:25 by ysoroko          ###   ########.fr       */
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

static char	*ft_extract_next_string(char *str)
{
	return (ft_strdup(str));
}

/*
** FT_INPUT_PARSING
** This is the central hub of the parsing of user's input
** It uses chained lists to divide input in several separated stings which
** will be read and executed as commands afterwards
** Returns a chained list containing every separate string from input
*/

t_list	*ft_input_parsing(char *input)
{
	t_list	*string_list;
	t_list	*new_member;
	int		i;
	char	*extracted_string;

	string_list = ft_lstnew(0);
	if (!string_list)
		exit(EXIT_FAILURE);
	i = -1;
	while (input[++i])
	{
		extracted_string = ft_extract_next_string(input);
		new_member = ft_lstnew(extracted_string);
		if (!new_member)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&string_list, new_member);
	}
	printf("INPUT READ: [%s]\n", input);
	return (string_list);
}
