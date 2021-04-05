/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/05 17:47:05 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termcap.h>
#include <termios.h>
#include "libft.h"

/*
** CONSTANT PARAMETERS
*/

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define INPUT_SIZE 1000
#define SPACES " \t\n\r\v\f"
#define SPACES_AND_REDIRECTIONS " \t\n\r\v\f><;|"
#define REDIRECTIONS "><;|"

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
t_command	*ft_new_t_command(char *name, char *flags, char *arg, char *redir);
void		ft_free_t_command(void *command_pointer);
void		ft_update_str_read_so_far(char *input_checkpnt, int i, char **prev);
t_command	*ft_extract_next_command(char *input_checkpnt, int *i);
void		ft_execute(t_list *command_list);
void		ft_signal_handler(int no_matter);
void		ft_initialize_termcaps(char **term_type, int *ret);
char		*ft_extract_next_command_string(char *input_checkpoint);

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