/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/25 14:09:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_display_prompt(char *color, char *prompt_name)
{
	write(STDOUT, color, 10);
	write(STDOUT, prompt_name, ft_strlen(prompt_name));
	write(STDOUT, COLOR_RESET, 5);
}

char	*ft_cut_string_at_char(char *str, char c)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			str[i] = 0;
	}
	return (str);
}

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