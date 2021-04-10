/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/10 15:04:02 by ysoroko          ###   ########.fr       */
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
** FT_EXTRACT_USER_INPUT_TO_STRING
** This function will transform user's input input into one string
** It will also check for unclosed quotes in the input
*/

static void	ft_extract_user_input_to_string(char **str)
{
	char	*temp;
	char	unclosed_quote;
	
	*str = ft_calloc_exit(sizeof(char), INPUT_SIZE);
	ft_read_exit(STDIN, *str, INPUT_SIZE);
	if (*str && !ft_str_only_has_chars_from_charset(*str, SPACES))
	{
		ft_check_for_unclosed_quotes(str);
		ft_cut_string_at_last_char(*str, '\n');
	}
	else
		ft_free_str(str);
}

/*
** FT_CLEANUP_AND_FREE
** This functions is responsible for freeing everything that was malloc'd
** during a single user's input
** It frees the input saved as a string, and also the entire t_list and
** all of its content
*/

static void	ft_cleanup_and_free(char **str, t_dl_lst *lst)
{
	ft_free_str(str);
	ft_dl_lstclear(lst, &ft_free_t_command);
}

/*
** FT_CHECK_FOR_UNCLOSED_QUOTES
** This function is used to analyze user's input
** and if it has unclosed quotes, it will display ">"
** in prompt until the unclosed quote is provided in input
*/

void	ft_check_for_unclosed_quotes(char **input)
{
	char	*additional_input;

	if (!input || !*input)
		return ;
	if (ft_str_has_unclosed_quotes(*input))
	{
		additional_input = ft_calloc_exit(sizeof(char), INPUT_SIZE);
		while (ft_str_has_unclosed_quotes(*input))
		{
			ft_display_prompt(BOLDCYAN, "> ");
			ft_read_exit(STDIN, additional_input, INPUT_SIZE);
			*input = ft_strjoin_free_pref_exit(input, additional_input);
		}
		ft_free_str(&additional_input);
	}
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
** After the parsing, it executes all of the commands from the user's input
** Cleans up and frees all used data after each user's input
*/

int	main(void)
{
	char		*user_input_str;
	t_dl_lst	*input_as_dl_command_list;

	ft_setup_signals();
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		ft_extract_user_input_to_string(&user_input_str);
		printf("input: [%s]\n", user_input_str);
		input_as_dl_command_list = ft_input_parsing(user_input_str);
		ft_execute(input_as_dl_command_list);
		ft_cleanup_and_free(&user_input_str, input_as_dl_command_list);
	}
	return (1);
}
