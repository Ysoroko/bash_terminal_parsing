/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/26 09:40:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/*
** CONSTANT PARAMETERS
*/

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define INPUT_SIZE 1000

/*
** STRUCTURES
*/

typedef	struct		s_command
{
	char	*name;
	char	*flags;
	char	*argument;
	char	*redirection;
}					t_command;

/*
** PROTOTYPES
*/

t_list		*ft_input_parsing(char *input);
void		ft_execute(t_list *input_list);
t_command	*ft_new_t_command(char *name, char *flags, char *arg, char *redir);

/*
** COLORS
*/

#define COLOR_RESET   "\x1b[0m"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif