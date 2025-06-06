/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:51 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 17:58:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"
#include "libft.h"
#include <stddef.h>

static size_t	print_char_padding_left(const t_format *f);
static size_t	print_char_padding_right(const t_format *f);

unsigned int	print_char(unsigned char c, const t_format *f)
{
	return (print_char_padding_left(f)
		+ ft_putnchar_fd(c, 1, f->fd)
		+ print_char_padding_right(f));
}

static size_t	print_char_padding_left(const t_format *f)
{
	if (!f->minus && f->width > 1)
		return (ft_putnchar_fd(' ', f->width - 1, f->fd));
	return (0);
}

static size_t	print_char_padding_right(const t_format *f)
{
	if (f->minus && f->width > 1)
		return (ft_putnchar_fd(' ', f->width - 1, f->fd));
	return (0);
}
