/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 17:32:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
** MAIN
** Central hub of the minishell project
** Initiates the minishell prompt, stores input and calls parsing to analyze
** user's input
*/

int main(void)
{
	char	*str;

	str = malloc(INPUT_SIZE);
	if (!str)
		exit(EXIT_FAILURE);
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		read(STDIN, str, INPUT_SIZE);
		str = ft_cut_string_at_char(str, '\n');
		ft_input_parsing(str);
		ft_free_and_realloc(str, INPUT_SIZE);
	}
	return (1);
}
