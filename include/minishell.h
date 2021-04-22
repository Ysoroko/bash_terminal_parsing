/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/22 11:09:46 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termcap.h>
# include <termios.h>
# include "libft.h"
# include <string.h>
# include <sys/errno.h>

/*
** CONSTANT PARAMETERS
*/

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INPUT_SIZE 1000
# define SPACES " \t\n\r\v\f"
# define REDIRECTIONS "><"
# define PIPES ";|"
# define SPACES_REDIRS_PIPES " \t\n\r\v\f><;|"
# define REDIRS_AND_PIPES "><;|"
# define SPACES_AND_PIPES " \t\n\r\v\f;|"
# define SPACES_AND_REDIRECTIONS " \t\n\r\v\f><"
# define BACKSLASH_IN_DOUBLE_QUOTES_CHARS "$`\"\\"

/*
** STRUCTURES
*/

typedef struct s_command
{
	char				*name;
	char				*flags;
	char				*argument;
	char				*redirection;
	char				*redir_arg;
	char				*result;
	char				pipe;
}	t_command;

/*
** PROTOTYPES
*/

t_dl_lst	*ft_input_parsing(char *input);
void		ft_free_t_command(void *command_pointer);
void		ft_update_str_read_so_far(char *input_checkpnt, int i, char **prev);
t_command	*ft_extract_next_command(char *input_checkpnt, int *i);
void		ft_execute(t_dl_lst *command_list);
void		ft_signal_handler(int no_matter);
void		ft_initialize_termcaps(char **term_type, int *ret);
char		*ft_extract_next_command_string(char *input_checkpoint);
void		ft_check_for_unclosed_quotes(char **input);
void		ft_check_for_pipe(char *str_command, t_command *command);
char		*ft_apply_quotes_and_env_vars(char *str);

/*
** COLORS
*/

# define COLOR_RESET   "\x1b[0m"

# define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif