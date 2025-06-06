/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:12 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 03:12:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "_ft_printf_shared.h"
#include "libft.h"
#include <stddef.h>

static unsigned int	print_nullptr(const t_format *f);
static unsigned int	puthex(size_t ptr, const t_format *f);
static unsigned int	ptrlen(size_t ptr);
static unsigned int	fullptrlen(unsigned int len_ptr, const t_format *f);

unsigned int	print_ptr(size_t ptr, const t_format *f)
{
	const unsigned int	len_ptr = ptrlen(ptr);
	const unsigned int	len_full = fullptrlen(len_ptr, f);

	if (ptr == 0)
		return (print_nullptr(f));
	return (print_ptr_padding_left(f, len_full)
		+ print_ptr_prefix(f)
		+ print_ptr_zero_padding(f, len_ptr, len_full)
		+ puthex(ptr, f)
		+ print_ptr_padding_right(f, len_full));
}

static unsigned int	print_nullptr(const t_format *f)
{
	const unsigned int	len = sizeof(NULL_PRINTOUT_PTR) - 1;
	unsigned int		printed;

	printed = 0;
	if (!f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	printed += ft_putnstr_fd(NULL_PRINTOUT_PTR, len, f->fd);
	if (f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	return (printed);
}

static unsigned int	puthex(size_t ptr, const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (ptr >= 16)
		printed += puthex(ptr / 16, f);
	ptr %= 16;
	if (ptr >= 10)
		printed += ft_putnchar_fd(ptr - 10 + 'a', 1, f->fd);
	else
		printed += ft_putnchar_fd(ptr + '0', 1, f->fd);
	return (printed);
}

static unsigned int	ptrlen(size_t ptr)
{
	unsigned int	len_ptr;

	len_ptr = 0;
	while (ptr > 0)
	{
		ptr /= 16;
		len_ptr++;
	}
	return (len_ptr);
}

static unsigned int	fullptrlen(unsigned int len_ptr, const t_format *f)
{
	unsigned int	len_full;

	len_full = len_ptr;
	if ((int)len_full < f->precision)
		len_full = f->precision;
	if (f->plus || f->space)
		len_full++;
	len_full += sizeof("0x") - 1;
	return (len_full);
}
