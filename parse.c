/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:50:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 13:50:15 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int	parse(const char *str, va_list ap, size_t i, int rt)
{
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] && str[i + 1] == 'c')
			i = i + printc(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == 's')
			i = i + prints(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'p')
			i = i + printp(ap, &rt);
		else if (str[i] == '%' && str[i + 1]
			&& (str[i + 1] == 'i' || str[i + 1] == 'd'))
			i = i + printd(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'u')
			i = i + printu(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'x')
			i = i + printx(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'X')
			i = i + printxx(ap, &rt);
		else if (str[i] == '%' && str[i + 1] && str[i + 1] == '%')
			i = i + printper(&rt);
		else if (str[i] == '%')
			return (-1);
		else if (str[i] != '%')
			ft_putchar_rt(*(str + i++), &rt);
	}
	return (rt);
}
