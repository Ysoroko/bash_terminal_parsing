/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/01 14:06:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
** FT_DISPLAY_PROMPT
** This function is used to display the prompt name on STDOUT in the specified
** color
*/

static void	ft_display_prompt(char *color, char *prompt_name)
{
	write(STDOUT, color, 10);
	write(STDOUT, prompt_name, (int)ft_strlen(prompt_name));
	write(STDOUT, "\x1b[0m", 5);
}

/*
** FT_INPUT_TO_STRING
** This function will transform user's input input into one string
*/

static void	ft_input_to_string(char **str)
{
	*str = malloc(INPUT_SIZE);
	if (!*str)
		exit(EXIT_FAILURE);
	if (read(STDIN, *str, INPUT_SIZE) < 0)
		exit(EXIT_FAILURE);
	if (str)
		*str = ft_cut_string_at_char(*str, '\n');
}

/*
** FT_CLEANUP_AND_FREE
** This functions is responsible for freeing everything that was malloc'd
** during a single user's input
*/

static void	ft_cleanup_and_free(char *str, t_list **lst)
{
	ft_free_str(str);
	ft_lstclear(lst, &ft_free_t_command);
}

/*
** FT_SETUP_SIGNALS
** This function modifies the behavious when specific actions are done
** When we press CTRL+D, it will not 
*/
static void	ft_setup_signals(void)
{
	signal(SIGINT, ft_signal_handler);
}

/*
** MAIN
** Central hub of the minishell project
** Initiates the minishell prompt, stores input and calls parsing to analyze
** user's input
** Cleans up and frees all used data after each user's input
*/

int	main(void)
{
	char	*str;
	t_list	*input_as_command_list;
	char	*term_type;
	int		ret;

	str = 0;
	input_as_command_list = 0;
	ft_initialize_termcaps(&term_type, &ret);
	ft_setup_signals();
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		ft_input_to_string(&str);
		if (str && str[0])
		{
			input_as_command_list = ft_input_parsing(str);
			ft_execute(input_as_command_list);
			ft_cleanup_and_free(str, 0);
		}
	}
	return (1);
}
