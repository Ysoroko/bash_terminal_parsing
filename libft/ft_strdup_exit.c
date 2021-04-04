/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:50:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/04 16:56:22 by ysoroko          ###   ########.fr       */
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

char	*ft_strdup_exit(const char *src)
{
	char	*str;
	char	*my_src;

	if (!src)
		return (0);
	my_src = (char *)(src);
	str = malloc(sizeof(*str) * (ft_strlen(my_src) + 1));
	if (!str)
		exit(EXIT_FAILURE);
	return (ft_strcpy(str, my_src));
}
