/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:11:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/06 11:21:40 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_dl_lst *dl_lst, int fd)
{
	t_command	*current_command;

	current_command = (t_command *)(dl_lst->content);
	if (current_command->flags)
		ft_putstr_fd(current_command->argument, fd);
	else
		ft_putendl_fd(current_command->argument, fd);
}
