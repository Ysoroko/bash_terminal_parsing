/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/30 16:37:14 by ysoroko          ###   ########.fr       */
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
	write(1, color, 10);
	write(1, prompt_name, (int)ft_strlen(prompt_name));
	write(1, "\x1b[0m", 5);
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
** FT_PRINT_COMMAND_LIST
** A debugging function used to print the list of our commands and related
** flags/arguments/redirections to make sure everything is running smoothly
*/

static void	ft_print_command_list(t_list *command_list)
{
	t_list		*current;
	t_command	*command;
	int			count;

	current = command_list->next;
	count = 1;
	while (current)
	{
		command = (t_command *)(current->content);
		printf("_______________________\n\n");
		printf("Element number: [%d]\n", count);
		//printf("command adress: [%p]\n", command);
		printf("Command name: [%s]\n", command->name);
		printf("Command flag: [%s]\n", command->flags);
		printf("Command argument: [%s]\n", command->argument);
		printf("Command redirection: [%s]\n", command->redirection);
		printf("_______________________\n\n");
		count++;
		current = current->next;
	}
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

	while (1)
	{
		ft_display_prompt(BOLDCYAN, "minishell: ");
		ft_input_to_string(&str);
		input_as_command_list = ft_input_parsing(str);
		ft_print_command_list(input_as_command_list);
		ft_cleanup_and_free(str, 0);
	}
	return (1);
}
