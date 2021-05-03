/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/03 14:49:18 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_FREE_T_COMMAND
** This function is used to free the t_command structure's elements,
** set al of them to NULL pointers using ft_free_str to avoid double free
** and then free and set t_command to NULL itself
*/

void	ft_free_t_command(void *command_pointer)
{
	t_command	*command;

	if (!command_pointer)
		return ;
	command = (t_command *)(command_pointer);
	if (command->name)
		ft_free_str(&(command->name));
	if (command->flags)
		ft_free_str(&(command->flags));
	if (command->argument)
		ft_free_str(&(command->argument));
	if (command->redirection)
		ft_free_str(&(command->redirection));
	if (command->result)
		ft_free_str(&(command->result));
	if (command->redir_arg)
		ft_free_str(&(command->redir_arg));
	free(command_pointer);
	command_pointer = 0;
}

/*
** FT_EXTRACT_NEXT_COMMAND_STRING
** This function will create a malloc'd duplicate of inupt_checkpoint
** argument, ending at the first redirection character
*/

char	*ft_extract_next_command_string(char *checkpoint)
{
	char	*ret;

	ret = ft_strdup_until_c_from_charset_not_quoted(checkpoint, PIPES);
	if (ft_str_only_has_chars_from_charset(ret, SPACES))
		ft_free_str(&ret);
	return (ret);
}

/*
** FT_CHECK_FOR_PIPE
** This functions checks if we have a redirection char in str_command
** argument and stores it in t_command "pipe" element
*/

void	ft_check_for_pipe(char *str_command, t_command *command)
{
	int	len;

	if (!str_command || !command)
		return ;
	len = ft_strlen(str_command);
	if (str_command[len - 1] == '|' || str_command[len - 1] == ';')
		command->pipe = str_command[len - 1];
}

/*
** ft_calculate_total_length_needed
** This funtion is used to calculate how many memory we need to allocate
** with malloc to create a duplicated copy of str argument
** while taking into account the environmental variables.
** It doesn't take quotes and escape characters into account
** so it returns a value bigger than necessary, which is later corrected
** in a different function
** Returns the number of bytes necessary for such malloc call
** Returns -1 if an invalid environmental name is used
*/

int	ft_calculate_total_length_needed(char *str)
{
	int		ret;
	int		i;
	char	*name;
	char	*value;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && ft_char_between_the_quotes(i, str) != '\'')
		{
			name = ft_extract_env_variable_name(&str[i], ENV_VAR_SEPARATORS);
			value = getenv(name);
			if (!value)
			{
				ft_free_str(&name);
				return (-1);
			}
			ret += ft_strlen(value);
			ft_free_str(&name);
		}
		else
			ret++;
	}
	return (ret);
}

/*
** ft_append_env_var_value
** Appends the value of env_name at the start of *str at the end of *dest
** str argument start with a '$' character when sent here
** At this point we already checked that str only contains valid env
** names so no need to double check here
*/

int	ft_append_env_var_value(char *str, char **dest, int *i, int *j)
{
	char	*temp;
	char	*env_name;
	char	*env_value;
	int		k;
	int		l;

	env_name = ft_extract_env_variable_name(str, ENV_VAR_SEPARATORS);
	env_value = getenv(env_name);
	k = 0;
	l = 0;

}