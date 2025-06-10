/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:44:54 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 13:44:57 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			size;

	if (str == NULL)
		return (-1);
	va_start(ap, str);
	size = parse(str, ap, 0, 0);
	va_end(ap);
	return (size);
}
