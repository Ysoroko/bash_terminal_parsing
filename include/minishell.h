/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/14 13:01:40 by ysoroko          ###   ########.fr       */
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
# define MAX_INPUT_SIZE 262144
# define SPACES " \t\n\r\v\f"
# define REDIRECTIONS "><"
# define PIPES ";|"
# define SPACES_REDIRS_PIPES " \t\n\r\v\f><;|"
# define REDIRS_AND_PIPES "><;|"
# define SPACES_AND_PIPES " \t\n\r\v\f;|"
# define REDIRS_PIPES_QUOTES "><|;\'\""
# define SPACES_AND_REDIRECTIONS " \t\n\r\v\f><"
# define BACKSLASH_IN_DQ_CHARS "$`\"\\\n"
# define ENV_VAR_SEPS " \t\n\r\v\f><;|\\"
# define COMMAND_NAMES "echo cd pwd export unset env exit"

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
void		ft_update_str_read_so_far(char *input_checkpt, int i, char **prev);
t_command	*ft_extract_next_command(char *input_checkpnt, int *i);
void		ft_execute(t_dl_lst *command_list);
int			ft_check_command_for_errors(t_command *command);
void		ft_signal_handler(int no_matter);
void		ft_initialize_termcaps(char **term_type, int *ret);
char		*ft_extract_next_command_string(char *input_checkpoint);
void		ft_check_for_unclosed_quotes(char **input);
void		ft_check_for_pipe(char *str_command, t_command *command);
char		*ft_apply_quotes_and_env_vars(char **str);
void		ft_append_env_var_value(char *str, char **dest, int *i, int *j);
int			ft_calculate_total_length_needed(char *str);
void		ft_quoted_copy(char *str, char **dest, int *i, int *j);
char		ft_env_var_delimiter(char *str_start_with_dollar_sign);
void		ft_add_words_after_redir_to_argument(t_command *command,
				char *red_pos);
void		ft_copy_spaces(char *src, char **dest, int *i, int *j);

/*
** FUNCTIONS
*/

void		ft_echo(t_dl_lst *dl_lst, int fd);

/*
** COLORS
*/

# define COLOR_RESET   "\x1b[0m"

# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

#endif