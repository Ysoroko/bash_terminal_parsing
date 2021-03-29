/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:11:12 by ysoroko           #+#    #+#             */
/*   Updated: 2021/03/29 16:30:37 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int		i;
	char	*my_src;

	my_src = (char *)(src);
	i = 0;
	while (my_src[i] != '\0')
	{
		dest[i] = my_src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strdup(const char *src)
{
	char *str;
	char *my_src;

	if (!src)
		return (0);
	my_src = (char *)(src);
	str = malloc(sizeof(*str) * (ft_strlen(my_src) + 1));
	if (str == 0)
		exit(EXIT_FAILURE);
	return (ft_strcpy(str, my_src));
}
