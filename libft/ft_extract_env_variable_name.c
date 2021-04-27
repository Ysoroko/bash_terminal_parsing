/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_env_variable_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:40:51 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/27 16:50:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** ft_determine_where_to_start_copying_the_name
** As its name suggests, this function will move the index to the character
** following the quotes (if any) or the $ sign (if no quotes).
** Returns the needed position to start copying the command's name
** With no dollar sign and no quotes it will return 0
*/

static int	ft_determine_where_to_start_copying_the_name(char *str)
{
	if (str[0] == '{' || str[0] == '(')
		return (1);
	else if (str[0] == '$')
	{
		if (str[1] == '{' || str[1] == '(')
			return (2);
		else
			return (1);
	}
	return (0);
}

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
	if (str[0] == '$')
	{
		if (str[1] == '{')
			*end = '}';
		else if (str[1] == '(')
			*end = ')';
	}
	else if (str[0] == '{')
		*end = '}';
	else if (str[0] == '(')
		*end = ')';
	else
		*end = 0;
	return (ft_determine_where_to_start_copying_the_name(str));
}

/*
** FT_EXTRACT_ENV_VARIABLE_NAME
** This function is called in minishell project when we see a '$' sign
** It will extract the variable name
*/

char	*ft_extract_env_variable_name(char *str, char *separators)
{
	int		i;
	int		j;
	char	end;
	char	*ret;
	char	*temp;

	if (!str)
		return (0);
	i = ft_determine_delimiters(str, &end);
	j = 0;
	if (!str)
		return (0);
	temp = ft_calloc_exit(ft_strlen(str), sizeof(char));
	if (end)
	{
		while (str[i] && str[i] != end)
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
