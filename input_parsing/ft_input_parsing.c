/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 17:38:34 by ysoroko          ###   ########.fr       */
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

void	ft_input_parsing(char *input)
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
	ft_lstclear(&string_list, free);
	printf("INPUT READ: [%s]\n", input);
}
