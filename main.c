/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/08 14:55:54 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
** FT_DISPLAY_PROMPT
** This function is used to display the prompt name on STDOUT in the specified
** color
** The last line is used to reset the color after displaying the prompt
** so that the input is written in standard white
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
	if (*str && (*str)[0] && !ft_str_only_has_chars_from_charset(*str, SPACES))
		*str = ft_cut_string_at_char(*str, '\n');
}

/*
** FT_CLEANUP_AND_FREE
** This functions is responsible for freeing everything that was malloc'd
** during a single user's input
** It frees the input saved as a string, and also the entire t_list and
** all of its content
*/

static void	ft_cleanup_and_free(char **str, t_list **lst)
{
	ft_free_str(str);
	ft_lstclear(lst, &ft_free_t_command);
}

/*
** FT_SETUP_SIGNALS
** This function modifies the behaviour when specific actions are done
** When we press CTRL+C, instead of quitting it will call the function
** ft_signal handler
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
	t_list	*all_user_input_list;
	char	*term_type;
	int		ret;

	str = 0;
	input_as_command_list = 0;
	all_user_input_list = 0;
	ft_setup_signals();
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		ft_input_to_string(&str);
		if (str && str[0])
		{
			input_as_command_list = ft_input_parsing(str);
			ft_execute(input_as_command_list);
		}
		ft_cleanup_and_free(&str, &input_as_command_list);
	}
	return (1);
}
