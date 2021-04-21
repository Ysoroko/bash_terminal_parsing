/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/21 11:47:41 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_single_quotes_copy
** This function is responsible for applying single quotes to a string
** Everything between two single quotes is copied as it is
** Escape characters and environment variables are ignored
*/

static void	ft_single_quotes_copy(char **t_str, char **t_ret, int *k, int *l)
{
	while ((*t_str)[*k] && (*t_str)[*k] != '\'') 
		{
			(*t_ret)[*l] = (*t_str)[*k];
			(*l)++;
			(*k)++;
		}
}

/*
** ft_double_quotes_copy
** This function is responsible for applying double quotes to a string
** Everything between two single quotes is copied as it is
** Escape characters and environment variables are ignored
*/

static void	ft_double_quotes_copy(char **t_str, char **t_ret, int *k, int *l)
{
	while ((*t_str)[*k] && (*t_str)[*k] != '\"') 
		{
			(*t_ret)[*l] = (*t_str)[*k];
			(*l)++;
			(*k)++;
		}
}

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
	if (quote == '\'')
		ft_single_quotes_copy(&temp_str, &temp_ret, &k, &l);
	else if (quote == '\"')
		ft_double_quotes_copy(&temp_str, &temp_ret, &k, &l);
	if (temp_str[k] == quote)
		k++;
	if (!k)
		*i += 1;
	else
		*i += k - 1;
	if (!l)
		*j += 1;
	else
		*j += l - 1;
	//printf("at the end:\n i: [%d]\n, j: [%d]\n", *i, *j);
}

/*
** FT_APPLY_QUOTES_AND_ENV_VARS
** This function will take a string filled in with quotes and if there
** are parts inside between quotes, it will "apply" those quotes.
** Returns a malloc'd string copy without quotes, but with quotes applied
** Example: ft_apply_quotes("${PWD}") will return "/Users/ysoroko/Minishell"
**			ft_apply_quotes('${PWD}') will return "${PWD}"
*/

char	*ft_apply_quotes_and_env_vars(char *str)
{
	int		i;
	int		j;
	char	*ret;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	ret = ft_calloc_exit(ft_strlen(str) + 1, sizeof(char));
	//printf("str before all: [%s]\n", str);
	while (str[i])
	{
		if (ft_char_is_a_start_quote(str, i))
		{
			//printf("ooh, a start quote! where &str[i] is: [%s]\n i: [%d]\n", &str[i], i);
			ft_quoted_copy(str, ret, &i, &j);
			//printf("ret after quoted copying: [%s]\n", ret);
			//printf("str after quoted copying: [%s]\n", &str[i]);
		}
		else
		{
			ret[j] = str[i];
			//printf("just copying ret: [%s]\n ret[j]: [%c]\n", ret, ret[j]);
		}
		//printf("ret loop inc: [%s]\n str[i]: [%c]\n", ret, str[i]);
		i++;
		j++;
	}
	return (ret);
}
