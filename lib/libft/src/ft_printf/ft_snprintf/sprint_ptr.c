/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:12 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 03:11:37 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include <stddef.h>

static void			sprint_nullptr(t_sformat *f);
static void			sputhex(size_t ptr, t_sformat *f);
static unsigned int	ptrlen(size_t ptr);
static unsigned int	fullptrlen(unsigned int len_ptr, const t_sformat *f);

void	sprint_ptr(size_t ptr, t_sformat *f)
{
	const unsigned int	len_ptr = ptrlen(ptr);
	const unsigned int	len_full = fullptrlen(len_ptr, f);

	if (ptr == 0)
	{
		sprint_nullptr(f);
		return ;
	}
	sprint_ptr_padding_left(f, len_full);
	sprint_ptr_prefix(f);
	sprint_ptr_zero_padding(f, len_ptr, len_full);
	sputhex(ptr, f);
	sprint_ptr_padding_right(f, len_full);
}

static void	sprint_nullptr(t_sformat *f)
{
	const unsigned int	len = sizeof(NULL_PRINTOUT_PTR) - 1;

	if (!f->minus && f->width > len)
		strcpy_char_record(f, ' ', f->width - len);
	strcpy_record(f, NULL_PRINTOUT_PTR, len);
	if (f->minus && f->width > len)
		strcpy_char_record(f, ' ', f->width - len);
}

static void	sputhex(size_t ptr, t_sformat *f)
{
	if (ptr >= 16)
		sputhex(ptr / 16, f);
	ptr %= 16;
	if (ptr >= 10)
		strcpy_char_record(f, ptr - 10 + 'a', 1);
	else
		strcpy_char_record(f, ptr + '0', 1);
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

static unsigned int	fullptrlen(unsigned int len_ptr, const t_sformat *f)
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
