/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:33:47 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/05 10:43:48 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_EXTRACT_ENV_VARIABLE_NAME
** This function is called in minishell project when we see a '$' sign
** str[0] must be a '$', otherwise an error will occur
** Returns a malloc'd name of the string or NULL if an error was detected
*/

char	*ft_extract_env_variable_name(char *str, char *separators)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	if (!str || str[0] != '$')
		return (0);
	j = 0;
	temp = ft_calloc_exit(ft_strlen(str), sizeof(char));
	while (str[i] && ft_is_env_name_char(str[i]))
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	return (ft_strdup_exit_and_free_src(&temp));
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
			name = ft_extract_env_variable_name(&str[i], ENV_VAR_SEPS);
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
	char	*env_name;
	char	*env_value;
	int		k;

	if (ft_char_is_a_start_quote(str, *i + 1))
	{
		//printf("hey, char after $ is a stat quote!\n");
		return ;
	}
	env_name = ft_extract_env_variable_name(str, ENV_VAR_SEPS);
	//printf("env_name in ft_append_env_var_value: [%s]\n", env_name);
	env_value = getenv(env_name);
	//printf("env_value in ft_append_env_var_value: [%s]\n", env_value);
	k = 1;
	while (str[k] && ft_is_env_name_char(str[k]))
			k++;
	*i += k - 1;
	//printf("dest before strcat of ft_append_env_var_value: [%s]\n", *dest);
	ft_strcat(*dest, env_value);
	//printf("dest at the end of ft_append_env_var_value: [%s]\n", *dest);
	*j += ft_strlen(env_value);
	ft_free_str(&env_name);
}
