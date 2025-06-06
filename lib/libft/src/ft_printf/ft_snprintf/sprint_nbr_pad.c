/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_nbr_pad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:34 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/09 23:34:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"

void	sprint_nbr_padding_left(t_sformat *f, char padding, \
								unsigned int len_full)
{
	if (!f->minus && f->width > len_full)
		strcpy_char_record(f, padding, f->width - len_full);
}

void	sprint_nbr_padding_right(t_sformat *f, unsigned int len_full)
{
	if (f->minus && f->width > len_full)
		strcpy_char_record(f, ' ', f->width - len_full);
}

void	sprint_nbr_zero_padding(t_sformat *f, unsigned int len_nbr)
{
	if (f->precision > (int)len_nbr)
		strcpy_char_record(f, '0', f->precision - len_nbr);
}
