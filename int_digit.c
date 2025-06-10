/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_digit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:33:57 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 19:33:58 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

size_t	printu(va_list ap, int *rt)
{
	ft_putu_len(va_arg(ap, int), rt);
	return (2);
}

size_t	printd(va_list ap, int *rt)
{
	int	n;

	n = va_arg(ap, int);
	ft_putnbr_len(n, rt);
	return (2);
}

void	ft_putu_len(unsigned int n, int *len)
{
	char	tmp;
	int		i;

	i = 0;
	if (n != 0)
	{
		tmp = (n % 10) + '0';
		if (n / 10 != 0)
			ft_putu_len(n / 10, len);
		i = write(1, &tmp, 1);
		*len = *len + i;
	}
	else if (n == 0)
	{
		i = write(1, "0", 1);
		*len = *len + i;
	}
}

void	ft_putnbr_len(int n, int *len)
{
	char	tmp;

	if (n == INT_MIN)
	{
		*len = *len + write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		*len = *len + write(1, "-", 1);
		ft_putnbr_len(-1 * n, len);
		return ;
	}
	else if (n != 0)
	{
		tmp = (n % 10) + '0';
		if (n / 10 != 0)
			ft_putnbr_len(n / 10, len);
		*len = *len + write(1, &tmp, 1);
	}
	else if (n == 0)
	{
		*len = *len + write(1, "0", 1);
		return ;
	}
}
