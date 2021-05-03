/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/03 12:01:55 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_check_for_errors
** This function simply checks if there are any wrong environmental
** variable names present in str and if so, prints the related error
** message using "strerror(errno)" and returns -1;
** Returns the result from ft_calculate_total_length_needed otherwise
** (a positive int)
*/

static int	ft_check_for_errors(char *str)
{
	int	ret;
	
	if (!str)
		return (-1);
	ret = ft_calculate_total_length_needed(str);
	if (ret == -1)
		strerror(errno);
	return (ret);
}

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
	char	*temp;
	char	*ret;

	if (!str || !(*str) || ft_check_for_errors(*str) == -1)
		return (0);
	my_str = *str;
	i = -1;
	j = 0;
	temp = ft_calloc_exit(ft_calculate_total_length_needed(*str), 1);
	while (my_str[++i])
	{
		if (my_str[i] == '\\')
			temp[j] = my_str[++i];
		else if (my_str[i] == '$')
		{
			ft_append_env_var_value(&(my_str[i]), &temp, &i, &j);
		}
	}

}
