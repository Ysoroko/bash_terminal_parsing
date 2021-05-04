/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/04 14:51:13 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_APPLY_QUOTES_AND_ENV_VARS
** This function will take a string filled in with quotes and if there
** are parts inside between quotes, it will "apply" those quotes.
** Returns a malloc'd string copy without quotes, but with quotes applied
** Example: ft_apply_quotes("${PWD}") will return "/Users/ysoroko/Minishell"
**			ft_apply_quotes('${PWD}') will return "${PWD}"
*/

char	*ft_apply_quotes_and_env_vars(char **str)
{
	int		i;
	int		j;
	char	*my_str;
	char	*ret;

	if (!str || !(*str))
		return (0);
	my_str = *str;
	i = -1;
	j = 0;
	ret = ft_calloc_exit(ft_calculate_total_length_needed(*str), 1);
	while (my_str[++i])
	{
		if (my_str[i] == '\\')
			ret[j] = my_str[++i];
		else if (my_str[i] == '$')
			ft_append_env_var_value(&(my_str[i]), &ret, &i, &j);
		else if (ft_char_is_a_start_quote(&(my_str[i]), i))
			ft_quoted_copy(&(my_str[i]), &ret, &i, &j);
	}

}
