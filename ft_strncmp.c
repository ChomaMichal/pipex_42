/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:12 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/22 17:19:04 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	counter = 0;
	while (counter != n)
	{
		if (!str1[counter] && !str2[counter])
			return (str1[counter] - str2 [counter]);
		if (str1[counter] != str2[counter])
			return (str1[counter] - str2 [counter]);
		counter ++;
	}
	return (0);
}
