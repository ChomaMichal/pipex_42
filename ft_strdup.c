/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:49:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/26 12:52:55 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	counter;
	char	*str;

	counter = 0;
	while (s[counter])
		counter ++;
	counter ++;
	str = malloc(sizeof(char) * counter);
	if (str == NULL)
		return (NULL);
	counter = 0;
	while (s[counter])
	{
		str[counter] = s[counter];
		counter ++;
	}
	str[counter] = 0;
	return (str);
}
