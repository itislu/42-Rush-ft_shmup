/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:38:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "_ft_printf_shared.h"
#include "libft.h"
#include <stddef.h>

static size_t		print_flags(const char *format, size_t *i, \
								const t_format *f);
static unsigned int	print_width(const char *format, size_t *i, \
								const t_format *f);
static unsigned int	print_precision(const char *format, size_t *i, \
									const t_format *f);

size_t	print_parsed(const char *format, size_t parsed, const t_format *f)
{
	size_t	i;
	size_t	printed;

	i = 0;
	printed = 0;
	if (format[0] == '%')
	{
		printed += ft_putnchar_fd('%', ++i, f->fd);
		printed += print_flags(format, &i, f);
		printed += print_width(format, &i, f);
		printed += print_precision(format, &i, f);
	}
	printed += ft_putnstr_fd(&format[i], parsed - i, f->fd);
	return (printed);
}

static size_t	print_flags(const char *format, size_t *i, const t_format *f)
{
	size_t	printed;

	printed = 0;
	if (f->hash)
		printed += ft_putnchar_fd('#', 1, f->fd);
	if (f->plus)
		printed += ft_putnchar_fd('+', 1, f->fd);
	if (f->space && !f->plus)
		printed += ft_putnchar_fd(' ', 1, f->fd);
	if (f->minus)
		printed += ft_putnchar_fd('-', 1, f->fd);
	if (f->zero && (!f->minus || f->minus == FROM_NEGATIVE_WIDTH))
		printed += ft_putnchar_fd('0', 1, f->fd);
	while (format[*i] != '\0' && ft_strchr(FLAGS, format[*i]) != NULL)
		(*i)++;
	return (printed);
}

static unsigned int	print_width(const char *format, size_t *i, \
								const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (f->width)
		printed += ft_putnbr_base_fd(f->width, "0123456789", f->fd);
	if (format[*i] == '*')
		(*i)++;
	else
		while (ft_isdigit(format[*i]))
			(*i)++;
	return (printed);
}

static unsigned int	print_precision(const char *format, size_t *i, \
									const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (f->precision >= 0)
	{
		printed += ft_putnchar_fd('.', 1, f->fd);
		(*i)++;
		printed += ft_putnbr_base_fd(f->precision, "0123456789", f->fd);
		if (format[*i] == '*')
			(*i)++;
		else
			while (ft_isdigit(format[*i]))
				(*i)++;
	}
	else if (f->precision == NEGATIVE_PRECISION)
		(*i) += 2;
	return (printed);
}
