/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command_for_errors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:19:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/06 12:20:00 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_check_name_for_errors
** This function is used to check if the command name is valid (it's a name
** of a command we need to implement in our minishell project)
** Returns 0 if no error was found and it's a valid name
** Returns 1 if the command name isn't a valid name and prints
** an error message "minishell: [command name]: command not found"
*/

static int	ft_check_name_for_errors(char *command_name)
{
	char	**possible_names;
	int		i;

	possible_names = ft_split(COMMAND_NAMES, ' ');
	if (!possible_names)
		exit(EXIT_FAILURE);
	i = -1;
	while (possible_names[++i])
	{
		if (!ft_strlcmp(command_name, possible_names[i]))
		{
			free(possible_names);
			possible_names = 0;
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(command_name, STDERR);
			ft_putendl_fd(": command not found", STDERR);
			return (0);
		}
	}
	free(possible_names);
	possible_names = 0;
	return (1);
}

/*
** ft_check_redirection_for_errors
** This function will check the redirection and its argument for errors
** Possible errors are: redirection present but no argument
*/

static int	ft_check_redirection_for_errors(t_command *command)
{
	if (command->redirection && !command->redir_arg)
	{
		//print bash: syntax error near unexpected token `x'
		ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR);
		if (!command->pipe)
			ft_putendl_fd("\'newline\'", STDERR);
		else
		{
			ft_putstr_fd('\'', STDERR);
			ft_putstr_fd(command->pipe, STDERR);
			ft_putendl_fd("\'", STDERR);
		}
		return (1);
	}

	return (0);
}

/*
** ft_check_command_for_errors
** This function will go through our t_dl_lst and will check each of its
** elements to see if there's an error/invalid combination present
*/

int	ft_check_command_for_errors(t_command *command)
{
	if (ft_check_name_for_errors(command->name))
		return (1);
	return (0);
}
