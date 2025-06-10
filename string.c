/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:10:15 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 19:10:16 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"

size_t	prints(va_list ap, int *rt)
{
	char	*str;
	int		i;

	str = va_arg(ap, char *);
	if (str == NULL)
	{
		i = putstr_len("(null)");
		*rt = *rt + i;
		return (2);
	}
	i = putstr_len(str);
	*rt = *rt + i;
	return (2);
}
