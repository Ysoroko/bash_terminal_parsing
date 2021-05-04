/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:33:47 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/04 12:36:52 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_env_var_delimiter
** This function checks if the first char following the '$' sign in the env var
** name in its argument starts with '{' or '('
** It will return the character which is expected to end the env var name
** Returns '}', ')' or '\0' if neither is true
*/

char	ft_env_var_delimiter(char *str_start_with_dollar_sign)
{
	char	ret;

	if (!str_start_with_dollar_sign || str_start_with_dollar_sign[0] != '$')
		return (0);
	if (str_start_with_dollar_sign[1] == '(')
		return (')');
	else if (str_start_with_dollar_sign[1] == '{')
		return ('}');
	return (0);
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
			if (value)
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

void	ft_append_env_var_value(char *str, char **dest, int *i, int *j)
{
	char	delimiter;
	char	*env_name;
	char	*env_value;
	int		k;

	delimiter = ft_env_var_delimiter(str);
	env_name = ft_extract_env_variable_name(str, ENV_VAR_SEPARATORS);
	env_value = getenv(env_name);
	k = 0;
	if (delimiter)
	{
		while (str[k] && str[k] != delimiter)
			k++;
	}
	else
	{
		while (str[k] && !ft_strchr(ENV_VAR_SEPARATORS, str[k]))
			k++;
	}
	*i += k;
	ft_strcat(*dest, env_value);
	*j += ft_strlen(env_name);
}
