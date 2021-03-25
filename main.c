/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 15:00:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int main(void)
{
	char	*str;

	str = malloc(100);
	
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		read(STDIN, str, 100);
		str = ft_cut_string_at_char(str, '\n');
		printf("INPUT READ: [%s]\n", str);
	}
	return (1);
}