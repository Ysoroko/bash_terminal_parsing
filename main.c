/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/09 14:02:26 by ysoroko          ###   ########.fr       */
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
	char	*temp;
	char	unclosed_quote;
	
	*str = malloc(INPUT_SIZE);
	if (!*str)
		exit(EXIT_FAILURE);
	if (read(STDIN, *str, INPUT_SIZE) < 0)
		exit(EXIT_FAILURE);
	if (*str && (*str)[0] && !ft_str_only_has_chars_from_charset(*str, SPACES))
		*str = ft_cut_string_at_char(*str, '\n');
	else
		ft_free_str(str);
	ft_check_for_unclosed_quotes(str);
}

/*
** FT_CLEANUP_AND_FREE
** This functions is responsible for freeing everything that was malloc'd
** during a single user's input
** It frees the input saved as a string, and also the entire t_list and
** all of its content
*/

static void	ft_cleanup_and_free(char **str, t_dl_lst **lst)
{
	ft_free_str(str);
	ft_dl_lstclear(*lst, &ft_free_t_command);
}

/*
** FT_CHECK_FOR_UNCLOSED_QUOTES
** This function is used to analyze user's input
** and if it has unclosed quotes, it will display ">"
** in prompt until the unclosed quote is provided
*/

void	ft_check_for_unclosed_quotes(char **input)
{
	char	unclosed_quote;
	char	*additional_input;
	char	*temp;
	int		read_ret;

	unclosed_quote = 0;
	if (ft_str_has_unclosed_quotes(*input) == 1)
		unclosed_quote = '\'';
	else if (ft_str_has_unclosed_quotes(*input) == 2)
		unclosed_quote = '\"';
	if (unclosed_quote)
	{
		additional_input = ft_calloc(sizeof(char), INPUT_SIZE);
		if (!additional_input)
			exit(EXIT_FAILURE);
		while (!ft_strchr(additional_input, unclosed_quote))
		{
			ft_display_prompt(BOLDCYAN, ">");
			read_ret = read(STDIN, additional_input, INPUT_SIZE);
			if (read_ret < 0)
				exit(EXIT_FAILURE);
			*input = ft_strjoin_free_pref_exit(input, additional_input);
		}
	}
	ft_free_str(&additional_input);
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
	char		*str;
	t_dl_lst	*input_as_command_list;
	char		*term_type;
	int			ret;

	str = 0;
	input_as_command_list = 0;
	ft_setup_signals();
	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		ft_input_to_string(&str);
		if (str)
		{
			input_as_command_list = ft_input_parsing(str);
			ft_execute(input_as_command_list);
		}
		ft_cleanup_and_free(&str, &input_as_command_list);
	}
	return (1);
}
