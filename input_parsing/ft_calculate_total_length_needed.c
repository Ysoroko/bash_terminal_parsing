/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_total_length_needed.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:02:37 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/03 11:27:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (str[i] == '$')
		{
			name = ft_extract_env_variable_name(&str[i], SPACES);
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
