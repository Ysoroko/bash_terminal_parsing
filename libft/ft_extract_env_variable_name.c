/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_env_variable_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:40:51 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/30 16:27:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** ft_determine_delimiters
** This function checks if the variable name is surrounded by {} or ()
** and/or start with '$' char.
** It then determines whether we need to copy until regular delimiters or
** only until the } or ).
** Returns the position of char where we need to start the copy
*/

static int	ft_determine_delimiters(char *str, char *end)
{
	if (!str || !end || str[0] != '$')
		return (-1);
	*end = 0;
	if (str[1] == '{')
	{
		*end = '}';
		return (2);
	}
	else if (str[1] == '(')
	{
		*end = ')';
		return (2);
	}
	return (1);
}

/*
** ft_check_for_errors
** As per subject our variable name is only supposed to be composed of 
** alphabetic characters, digits and '_' characters
** This function checks if there are any other characters present and if so,
** it returns 1
** Returns 0 otherwise
*/

static int	ft_check_for_errors(char *str, char end)
{
	int	i;

	if (end)
		i = 2;
	else
		i = 1;
	while (str[i++] && str[i] != end)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
	}
	return (0);
}

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
	char	end;
	char	*ret;
	char	*temp;

	i = ft_determine_delimiters(str, &end);
	if (!str || str[0] != '$' || ft_check_for_errors(str, end))
		return (0);
	j = 0;
	temp = ft_calloc_exit(ft_strlen(str), sizeof(char));
	if (end)
	{
		while (str[i] && str[i] != end && !ft_strchr(separators, str[i]))
			temp[j++] = str[i++];
		if (str[i] != end)
			return (ft_free_str(&temp));
	}
	else
	{
		while (str[i] && !ft_strchr(separators, str[i]))
			temp[j++] = str[i++];
	}
	ret = ft_strdup_exit(temp);
	ft_free_str(&temp);
	return (ret);
}
