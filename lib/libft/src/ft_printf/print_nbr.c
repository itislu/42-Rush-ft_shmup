/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:55 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/08 01:05:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "libft.h"
#include <stddef.h>

static unsigned int	nbrlen(long nbr, const t_format *f);
static unsigned int	fullnbrlen(long nbr, unsigned int len_nbr, \
								const t_format *f);
static unsigned int	print_prefix(long nbr, const t_format *f);
static unsigned int	print_nbr_in_correct_base(long nbr, const t_format *f);

unsigned int	print_nbr(long nbr, const t_format *f)
{
	const unsigned int	len_nbr = nbrlen(nbr, f);
	const unsigned int	len_full = fullnbrlen(nbr, len_nbr, f);
	char				padding;
	unsigned int		printed;

	if (f->zero && !f->minus && f->precision < 0)
		padding = '0';
	else
		padding = ' ';
	printed = 0;
	if (padding == '0' && f->specifier != 'u')
		printed += print_prefix(nbr, f);
	printed += print_nbr_padding_left(f, padding, len_full);
	if (padding == ' ' && f->specifier != 'u'
		&& !(nbr == 0 && f->precision == 0))
		printed += print_prefix(nbr, f);
	printed += print_nbr_zero_padding(f, len_nbr);
	if (!(nbr == 0 && f->precision == 0))
		printed += print_nbr_in_correct_base(nbr, f);
	printed += print_nbr_padding_right(f, len_full);
	return (printed);
}

static unsigned int	nbrlen(long nbr, const t_format *f)
{
	unsigned int	base;

	if (nbr == 0 && f->precision == 0)
		return (0);
	if (ft_strchr("xX", f->specifier) != NULL)
		base = 16;
	else
		base = 10;
	return (ft_nbrlen_base_u(ft_labs_u(nbr), base));
}

static unsigned int	fullnbrlen(long nbr, unsigned int len_nbr, \
								const t_format *f)
{
	unsigned int	len_full;

	len_full = len_nbr;
	if ((int)len_nbr < f->precision)
		len_full = f->precision;
	if (ft_strchr("uxX", f->specifier) == NULL)
		if (!(nbr == 0 && f->precision == 0))
			if (nbr < 0 || f->plus || f->space)
				len_full++;
	if (ft_strchr("xX", f->specifier) != NULL)
		if (f->hash && nbr != 0)
			len_full += sizeof("0x") - 1;
	return (len_full);
}

static unsigned int	print_prefix(long nbr, const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (ft_strchr("xX", f->specifier) != NULL)
	{
		if (f->hash && nbr != 0)
		{
			if (f->specifier == 'x')
				printed += ft_putnstr_fd("0x", 2, f->fd);
			else if (f->specifier == 'X')
				printed += ft_putnstr_fd("0X", 2, f->fd);
		}
	}
	else
	{
		if (nbr < 0)
			printed += ft_putnchar_fd('-', 1, f->fd);
		else if (f->plus)
			printed += ft_putnchar_fd('+', 1, f->fd);
		else if (f->space)
			printed += ft_putnchar_fd(' ', 1, f->fd);
	}
	return (printed);
}

static unsigned int	print_nbr_in_correct_base(long nbr, const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (f->specifier == 'x')
		printed += ft_putnbr_base_fd(nbr, "0123456789abcdef", f->fd);
	else if (f->specifier == 'X')
		printed += ft_putnbr_base_fd(nbr, "0123456789ABCDEF", f->fd);
	else
		printed += ft_putnbr_base_fd(ft_labs(nbr), "0123456789", f->fd);
	return (printed);
}
