/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:41:25 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:02:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "_ft_printf_shared.h"
#include "libft.h"
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>

size_t	parseandprint(const char *format, size_t *i, t_format *f, va_list *ap)
{
	size_t	printed;
	size_t	parsed;

	printed = 0;
	parsed = 1;
	if (format[(*i)++] == '%')
	{
		parsed += set_format(format, i, f, ap);
		if (format[*i] == '\0' && f->specifier == '\0' && !f->unresolved)
		{
			errno = EINVAL;
			return (printed);
		}
		if (f->specifier != '\0')
			printed += print_argument(f, ap);
	}
	if (f->specifier == '\0')
		printed += print_parsed(&format[*i - parsed], parsed, f);
	return (printed);
}

size_t	print_argument(const t_format *f, va_list *ap)
{
	size_t	printed;

	printed = 0;
	if (f->specifier == 'c')
		printed = print_char((unsigned char)va_arg(*ap, int), f);
	else if (f->specifier == 's')
		printed = print_str(va_arg(*ap, const char *), f);
	else if (f->specifier == 'p')
		printed = print_ptr((size_t)va_arg(*ap, void *), f);
	else if (f->specifier == 'd' || f->specifier == 'i')
		printed = print_nbr((long)va_arg(*ap, int), f);
	else if (f->specifier == 'u')
		printed = print_nbr((long)va_arg(*ap, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		printed = print_nbr((long)va_arg(*ap, unsigned int), f);
	else if (f->specifier == '%')
		printed = ft_putnchar_fd('%', 1, f->fd);
	return (printed);
}

void	reset_format(t_format *f)
{
	f->hash = false;
	f->plus = false;
	f->space = false;
	f->minus = 0;
	f->zero = false;
	f->width = 0;
	f->precision = NO_PRECISION_SET;
	f->specifier = '\0';
}
