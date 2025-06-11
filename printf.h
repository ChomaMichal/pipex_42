/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:50:46 by mchoma            #+#    #+#             */
/*   Updated: 2025/05/09 13:50:48 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
//# include <stddef.h>
# include <limits.h>
# include <stdarg.h>

size_t	printc(va_list ap, int *rt);
size_t	printxx(va_list ap, int *rt);
size_t	printx(va_list ap, int *rt);
void	ft_puthexd_len(unsigned long n, int *len, char *arr);
size_t	printp(va_list ap, int *rt);
// takes any amount of argumetns
int		ft_printf(const char *str, ...);
size_t	printu(va_list ap, int *rt);
size_t	printd(va_list ap, int *rt);
size_t	printi(va_list ap, int *rt);
void	ft_putu_len(unsigned int n, int *len);
void	ft_putnbr_len(int n, int *len);
int		parse(const char *str, va_list ap, size_t i, int rt);
size_t	printper(int *rt);
size_t	prints(va_list ap, int *rt);
int		putstr_len(char *str);
void	ft_putchar_rt(char c, int *rt);
size_t	ft_strlen(const char *str);

#endif 
