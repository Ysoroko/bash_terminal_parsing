/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/16 10:50:27 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	ft_quoted_copy(char *str, char *ret, int *i, int *j)
{
	char	*temp_str;
	char	*temp_ret;
	char	quote;
	int		k;
	int		l;

	quote = str[*i];
	k = 1;
	l = 0;
	temp_str = &(str[*i]);
	temp_ret = &(ret[*j]);
	//printf("quote in quoted copy: [%c]\n i: [%d]\n j: [%d]\n", quote, *i, *j);
	if (*i && str[*i - 1] == quote && ret[*j - 1] == quote)
		l = -1;
	if (quote == '\'' || quote == '\"')
	{
		while (temp_str[k] && temp_str[k] != quote) 
		{
			temp_ret[l] = temp_str[k];
			l++;
			k++;
		}
	}
	if (temp_str[k] == quote)
		k++;
	*i += k;
	*j += l;
	//printf("at the end:\n i: [%d]\n, j: [%d]\n", *i, *j);
}

/*
** FT_APPLY_QUOTES
** This function will take a string filled in with quotes and if there
** are parts inside between quotes, it will "apply" those quotes.
** Returns a malloc'd string copy without quotes, but with quotes applied
** Example: ft_apply_quotes("${PWD}") will return "/Users/ysoroko/Minishell"
**			ft_apply_quotes('${PWD}') will return "${PWD}"
*/

char	*ft_apply_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	ret = ft_calloc_exit(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (ft_char_is_a_start_quote(str, i))
			ft_quoted_copy(str, ret, &i, &j);
		else

			ret[j] = str[i];
		i++;
		j++;
	}
	return (ret);
}
