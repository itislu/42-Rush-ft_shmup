/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_ptr_pad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:02:01 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/09 23:45:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"

void	sprint_ptr_padding_left(t_sformat *f, unsigned int len_full)
{
	if (!f->minus && f->width > len_full && !(f->zero && f->precision < 0))
		strcpy_char_record(f, ' ', f->width - len_full);
}

void	sprint_ptr_padding_right(t_sformat *f, unsigned int len_full)
{
	if (f->minus && f->width > len_full)
		strcpy_char_record(f, ' ', f->width - len_full);
}

void	sprint_ptr_prefix(t_sformat *f)
{
	if (f->plus)
		strcpy_char_record(f, '+', 1);
	else if (f->space)
		strcpy_char_record(f, ' ', 1);
	strcpy_record(f, "0x", 2);
}

void	sprint_ptr_zero_padding(t_sformat *f, unsigned int len_ptr, \
								unsigned int len_full)
{
	if (f->precision > (int)len_ptr)
		strcpy_char_record(f, '0', f->precision - len_ptr);
	else if (f->zero && !f->minus && f->precision < 0 && f->width > len_full)
		strcpy_char_record(f, '0', f->width - len_full);
}
