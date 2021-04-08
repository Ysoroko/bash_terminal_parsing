/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/08 15:25:13 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_PRINT_COMMAND_LIST
** A debugging function used to print the list of our commands and related
** flags/arguments/redirections to make sure everything is running smoothly
*/

static void	ft_print_command_list(void *current_command)
{
	t_command	*command;
	int			spaces;
	char		*prev_address;

	prev_address = 0;
	spaces = -16;
	printf("\n\n\n");
	command = (t_command *)(current_command);
	if (command && command->prev_command)
		prev_address = command->prev_command->name;
	printf("_________________________________________\n\n");
	printf("%*s [%s]\n", spaces, "Command:", command->name);
	printf("%*s [%s]\n", spaces, "Flag:", command->flags);
	printf("%*s [%s]\n", spaces, "Argument:", command->argument);
	printf("%*s [%s]\n", spaces, "Redirection:", command->redirection);
	printf("%*s [%s]\n", spaces, "Previous:", prev_address);
	printf("_________________________________________\n\n");
}

/*
** FT_EXECUTE_CORRESPONDING_COMMAND
** This function is used in ft_lstmap. It checks each t_command structure's
** name and calls the corresponding function executed with t_command's argument
** and flag
**
**static void	*ft_execute_corresponding_command(void *current_command)
**{
**	t_command *command;
**
**	command = (t_command *)(current_command);
**	if (!strcmp(command->name, "echo"))
**		ft_echo(command->flags, command->argument);
**	if (!strcmp(command->name, "pwd"))
**		ft_pwd(command->flags, command->argument);
**	if (!strcmp(command->name, "cd"))
**		ft_cd(command->flags, command->argument);
**	if (!strcmp(command->name, "export"))
**		ft_export(command->flags, command->argument);
**	if (!strcmp(command->name, "unset"))
**		ft_unset(command->flags, command->argument);
**	if (!strcmp(command->name, "env"))
**		ft_env(command->flags, command->argument);
**	if (!strcmp(command->name, "exit"))
**		ft_exit(command->flags, command->argument);
**	return (0);
**}
*/

/*
** FT_EXECUTE
** This function is the main bridge between parsing and executing commands
** It takes the parsing as a t_list* structure, passes it to a different
** function which will execute all the commands for every element of 
** the t_list* structure
*/

void	ft_execute(t_list *command_list)
{
	ft_lstiter(command_list, ft_print_command_list);
}
