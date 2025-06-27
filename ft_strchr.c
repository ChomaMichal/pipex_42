/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:07:45 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/22 17:11:30 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	counter;

	counter = 0;
	while (s[counter])
	{
		if (s[counter] == c)
			return ((char *)&s[counter]);
		counter ++;
	}
	if (c == 0)
		return ((char *) & s[counter]);
	return (0);
}
