/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:13:41 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 14:13:43 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int	putstr_len(char *str)
{
	int	len;

	len = ft_strlen(str);
	return (write(1, str, len));
}

void	ft_putchar_rt(char c, int *rt)
{
	int	i;

	i = 0;
	i = write(1, &c, 1);
	*rt = *rt + i;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
