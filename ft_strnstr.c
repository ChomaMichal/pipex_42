/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:32:43 by mchoma            #+#    #+#             */
/*   Updated: 2025/04/22 17:39:53 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = len;
	j = 0;
	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while ((little[j] == big[i + j]) && little[j] && i + j < len)
				j ++;
			if (little[j] == 0)
				return ((char *) & big[i]);
			j = 0;
		}
		i++;
	}
	return (0);
}
