/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:01:47 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/03 15:07:22 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
