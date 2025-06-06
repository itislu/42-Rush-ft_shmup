/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:17 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:06:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "_ft_printf_shared.h"
#include "libft.h"
#include <stddef.h>

static size_t	print(const char *str, size_t len, const t_format *f);
static size_t	print_str_padding_left(const t_format *f, size_t len);
static size_t	print_str_padding_right(const t_format *f, size_t len);

size_t	print_str(const char *str, const t_format *f)
{
	size_t	len;
	size_t	printed;

	printed = 0;
	if (str == NULL)
	{
		len = sizeof(NULL_PRINTOUT_STR) - 1;
		if (f->precision >= 0 && len > (size_t)f->precision)
			len = 0;
		printed += print(NULL_PRINTOUT_STR, len, f);
	}
	else
	{
		len = ft_strlen(str);
		if (f->precision >= 0 && len > (size_t)f->precision)
			len = f->precision;
		printed += print(str, len, f);
	}
	return (printed);
}

static size_t	print(const char *str, size_t len, const t_format *f)
{
	return (print_str_padding_left(f, len)
		+ ft_putnstr_fd(str, len, f->fd)
		+ print_str_padding_right(f, len));
}

static size_t	print_str_padding_left(const t_format *f, size_t len)
{
	if (!f->minus && f->width > len)
		return (ft_putnchar_fd(' ', f->width - len, f->fd));
	return (0);
}

static size_t	print_str_padding_right(const t_format *f, size_t len)
{
	if (f->minus && f->width > len)
		return (ft_putnchar_fd(' ', f->width - len, f->fd));
	return (0);
}
