/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:55 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/08 01:05:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "libft.h"
#include <stddef.h>

static unsigned int	nbrlen(long nbr, const t_sformat *f);
static unsigned int	fullnbrlen(long nbr, unsigned int len_nbr, \
								const t_sformat *f);
static void			sprint_prefix(long nbr, t_sformat *f);
static void			sprint_nbr_in_correct_base(long nbr, t_sformat *f);

void	sprint_nbr(long nbr, t_sformat *f)
{
	const unsigned int	len_nbr = nbrlen(nbr, f);
	const unsigned int	len_full = fullnbrlen(nbr, len_nbr, f);
	char				padding;

	if (f->zero && !f->minus && f->precision < 0)
		padding = '0';
	else
		padding = ' ';
	if (padding == '0' && f->specifier != 'u')
		sprint_prefix(nbr, f);
	sprint_nbr_padding_left(f, padding, len_full);
	if (padding == ' ' && f->specifier != 'u'
		&& !(nbr == 0 && f->precision == 0))
		sprint_prefix(nbr, f);
	sprint_nbr_zero_padding(f, len_nbr);
	if (!(nbr == 0 && f->precision == 0))
		sprint_nbr_in_correct_base(nbr, f);
	sprint_nbr_padding_right(f, len_full);
}

static unsigned int	nbrlen(long nbr, const t_sformat *f)
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
								const t_sformat *f)
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

static void	sprint_prefix(long nbr, t_sformat *f)
{
	if (ft_strchr("xX", f->specifier) != NULL)
	{
		if (f->hash && nbr != 0)
		{
			if (f->specifier == 'x')
				strcpy_record(f, "0x", 2);
			else if (f->specifier == 'X')
				strcpy_record(f, "0X", 2);
		}
	}
	else
	{
		if (nbr < 0)
			strcpy_char_record(f, '-', 1);
		else if (f->plus)
			strcpy_char_record(f, '+', 1);
		else if (f->space)
			strcpy_char_record(f, ' ', 1);
	}
}

static void	sprint_nbr_in_correct_base(long nbr, t_sformat *f)
{
	if (f->specifier == 'x')
		strcpy_nbr_record(f, nbr, "0123456789abcdef");
	else if (f->specifier == 'X')
		strcpy_nbr_record(f, nbr, "0123456789ABCDEF");
	else
		strcpy_nbr_record(f, ft_labs(nbr), "0123456789");
}
