/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:17 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:01:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include "libft.h"
#include <stddef.h>

static void	sprint(const char *str, size_t len, t_sformat *f);
static void	sprint_str_padding_left(t_sformat *f, size_t len);
static void	sprint_str_padding_right(t_sformat *f, size_t len);

void	sprint_str(const char *str, t_sformat *f)
{
	size_t	len;

	if (str == NULL)
	{
		len = sizeof(NULL_PRINTOUT_STR) - 1;
		if (f->precision >= 0 && len > (size_t)f->precision)
			len = 0;
		sprint(NULL_PRINTOUT_STR, len, f);
	}
	else
	{
		len = ft_strlen(str);
		if (f->precision >= 0 && len > (size_t)f->precision)
			len = f->precision;
		sprint(str, len, f);
	}
}

static void	sprint(const char *str, size_t len, t_sformat *f)
{
	sprint_str_padding_left(f, len);
	strcpy_record(f, str, len);
	sprint_str_padding_right(f, len);
}

static void	sprint_str_padding_left(t_sformat *f, size_t len)
{
	if (!f->minus && f->width > len)
		strcpy_char_record(f, ' ', f->width - len);
}

static void	sprint_str_padding_right(t_sformat *f, size_t len)
{
	if (f->minus && f->width > len)
		strcpy_char_record(f, ' ', f->width - len);
}
