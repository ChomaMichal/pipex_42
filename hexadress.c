/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smalhex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:26:37 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 19:26:38 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

size_t	printxx(va_list ap, int *rt)
{
	ft_puthexd_len(va_arg(ap, unsigned int), rt, "0123456789ABCDEF");
	return (2);
}

size_t	printx(va_list ap, int *rt)
{
	ft_puthexd_len(va_arg(ap, unsigned int), rt, "0123456789abcdef");
	return (2);
}

void	ft_puthexd_len(unsigned long n, int *len, char *arr)
{
	int	i;

	if (n != 0)
	{
		if (n / 16 != 0)
			ft_puthexd_len(n / 16, len, arr);
		i = write(1, arr + (n % 16), 1);
		*len = *len + i;
	}
	else if (n == 0)
	{
		i = write(1, "0", 1);
		*len = *len + i;
	}
}

size_t	printp(va_list ap, int *rt)
{
	unsigned long	ptr;
	int				i;

	ptr = va_arg(ap, unsigned long);
	if (ptr == 0)
	{
		*rt = putstr_len("(nil)") + *rt;
		return (2);
	}
	i = write(1, "0x", 2);
	*rt = *rt + i;
	ft_puthexd_len(ptr, rt, "0123456789abcdef");
	return (2);
}
