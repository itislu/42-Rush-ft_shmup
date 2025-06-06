/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr_pad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:49 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 18:15:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "libft.h"

unsigned int	print_ptr_padding_left(const t_format *f, unsigned int len_full)
{
	if (!f->minus && f->width > len_full && !(f->zero && f->precision < 0))
		return (ft_putnchar_fd(' ', f->width - len_full, f->fd));
	return (0);
}

unsigned int	print_ptr_padding_right(const t_format *f, \
										unsigned int len_full)
{
	if (f->minus && f->width > len_full)
		return (ft_putnchar_fd(' ', f->width - len_full, f->fd));
	return (0);
}

unsigned int	print_ptr_prefix(const t_format *f)
{
	unsigned int	printed;

	printed = 0;
	if (f->plus)
		printed += ft_putnchar_fd('+', 1, f->fd);
	else if (f->space)
		printed += ft_putnchar_fd(' ', 1, f->fd);
	printed += ft_putnstr_fd("0x", 2, f->fd);
	return (printed);
}

unsigned int	print_ptr_zero_padding(const t_format *f, \
										unsigned int len_ptr, \
										unsigned int len_full)
{
	if (f->precision > (int)len_ptr)
		return (ft_putnchar_fd('0', f->precision - len_ptr, f->fd));
	if (f->zero && !f->minus && f->precision < 0 && f->width > len_full)
		return (ft_putnchar_fd('0', f->width - len_full, f->fd));
	return (0);
}
