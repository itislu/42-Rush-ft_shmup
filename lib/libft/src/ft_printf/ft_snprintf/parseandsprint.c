/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandsprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:41:25 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 01:54:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include <stdarg.h>
#include <stddef.h>

void	parseandsprint(const char *format, size_t *i, t_sformat *f, va_list *ap)
{
	size_t	parsed;

	parsed = 1;
	if (format[(*i)++] == '%')
	{
		parsed += set_sformat(format, i, f, ap);
		if (format[*i] == '\0' && f->specifier == '\0' && !f->unresolved)
		{
			f->chars_needed = -1;
			return ;
		}
		if (f->specifier != '\0')
			sprint_argument(f, ap);
	}
	if (f->specifier == '\0')
		sprint_parsed(&format[*i - parsed], parsed, f);
}

void	sprint_argument(t_sformat *f, va_list *ap)
{
	if (f->specifier == 'c')
		sprint_char((unsigned char)va_arg(*ap, int), f);
	else if (f->specifier == 's')
		sprint_str(va_arg(*ap, const char *), f);
	else if (f->specifier == 'p')
		sprint_ptr((size_t)va_arg(*ap, void *), f);
	else if (f->specifier == 'd' || f->specifier == 'i')
		sprint_nbr((long)va_arg(*ap, int), f);
	else if (f->specifier == 'u')
		sprint_nbr((long)va_arg(*ap, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		sprint_nbr((long)va_arg(*ap, unsigned int), f);
	else if (f->specifier == '%')
		strcpy_char_record(f, '%', 1);
}

void	reset_sformat(t_sformat *f)
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
