/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/22 14:53:18 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_extract_env_variable
** When we see a "$" (not after a '\'), we are replacing all that follows
** by the value of the related environmental variable
*/

static int	ft_extract_env_variable(char *str, char **ret, int *i, int *j)
{
	char	*temp_ret;
	char	*env_name;
	char	*env_value;

	env_name = ft_extract_first_word_alpha_underscore(&(str[*i]), SPACES);
	printf("env_name: [%s]\n", env_name);
	env_value = getenv(env_name);
	printf("env_value: [%s]\n", env_value);
	if (!env_value)
	{
		ft_putendl_fd(strerror(errno), STDERR);
		ft_free_str(&env_name);
		return (-1);
	}
	*ret = ft_strjoin_free_pref_exit(ret, env_value);
	while (str[*i] && ((!ft_isalpha(str[*i]) && str[*i] != '_')
		|| ft_strchr(SPACES, str[*i])))
		*i += 1;
	while (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_')
		&& !ft_strchr(SPACES, str[*i]))
		*i += 1;
	while (str[*i] && ((!ft_isalpha(str[*i]) && str[*i] != '_')
		&& !ft_strchr(SPACES, str[*i])))
		*i += 1;
	if (*i)
		*i -= 1;
	*j = ft_strlen(*ret) - 1;
	ft_free_str(&env_name);
	printf("str after extracting env variable: [%s]\n", str);
	printf("ret after extracting env variable: [%s]\n", *ret);
	return (0);
}

/*
** ft_double_quotes_copy
** This function is responsible for applying double quotes to a string
** Everything between two single quotes is copied as it is
** Escape characters and environment variables are ignored
** Returns 0 if everything went right and -1 if an error was encountered
*/

static int	ft_double_quotes_copy(char **t_str, char **t_ret, int *k, int *l)
{
	while ((*t_str)[*k] && ft_char_is_a_start_quote(*t_str, *k) != '\"') 
	{
		if ((*t_str)[*k] == '\\'
			&& ft_strchr(BACKSLASH_IN_DOUBLE_QUOTES_CHARS, (*t_str)[*k + 1]))
		{
			(*k) += 1;
			(*t_ret)[*l] = (*t_str)[*k];
		}
		else if (ft_char_is_a_dollar_sign(*t_str, *k))
		{
			if (ft_extract_env_variable(*t_str, t_ret, k, l) == -1)
				return (-1);
			printf("t_ret after extracting env variable: [%s]\n", *t_ret);
		}
		else
			(*t_ret)[*l] = (*t_str)[*k];
		(*l)++;
		(*k)++;
	}
	return (0);
}

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
** ft_quoted_copy
*/

static	int	ft_quoted_copy(char *str, char *ret, int *i, int *j)
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
	{
		if (ft_double_quotes_copy(&temp_str, &temp_ret, &k, &l) == -1)
			return (-1);
		printf("temp_ret after double_quotes_copy: [%s]\n", temp_ret);
	}
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
	return (0);
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
		if (str[i] == '\\')
		{
			i++;
			ret[j] = str[i];
		}
		else if (ft_char_is_a_start_quote(str, i))
		{
			if (ft_quoted_copy(str, ret, &i, &j) == -1)
				return (ft_free_str(&ret));
		}
		else if (ft_char_is_a_dollar_sign(str, i))
		{
			if (ft_extract_env_variable(str, &ret, &i, &j) == -1)
				return (ft_free_str(&ret));
		}
		else
			ret[j] = str[i];
		//printf("ret loop inc: [%s]\n str[i]: [%c]\n, i: [%d]\n, ret[j]: [%c]\n, j: [%d]\n", ret, str[i], i,str[j], j);
		if (str[i])
		{
			i++;
			j++;
		}
	}
	printf("ret after ft_apply_quotes: [%s]\n", ret);
	return (ret);
}
