/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_parsed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:36:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include "libft.h"
#include <stddef.h>

static void	sprint_flags(const char *format, size_t *i, t_sformat *f);
static void	sprint_width(const char *format, size_t *i, t_sformat *f);
static void	sprint_precision(const char *format, size_t *i, t_sformat *f);

void	sprint_parsed(const char *format, size_t parsed, t_sformat *f)
{
	size_t	i;

	i = 0;
	if (format[0] == '%')
	{
		strcpy_char_record(f, '%', 1);
		i++;
		sprint_flags(format, &i, f);
		sprint_width(format, &i, f);
		sprint_precision(format, &i, f);
	}
	strcpy_record(f, &format[i], parsed - i);
}

static void	sprint_flags(const char *format, size_t *i, t_sformat *f)
{
	if (f->hash)
		strcpy_char_record(f, '#', 1);
	if (f->plus)
		strcpy_char_record(f, '+', 1);
	if (f->space && !f->plus)
		strcpy_char_record(f, ' ', 1);
	if (f->minus)
		strcpy_char_record(f, '-', 1);
	if (f->zero && (!f->minus || f->minus == FROM_NEGATIVE_WIDTH))
		strcpy_char_record(f, '0', 1);
	while (format[*i] != '\0' && ft_strchr(FLAGS, format[*i]) != NULL)
		(*i)++;
}

static void	sprint_width(const char *format, size_t *i, t_sformat *f)
{
	if (f->width)
		strcpy_nbr_record(f, f->width, "0123456789");
	if (format[*i] == '*')
		(*i)++;
	else
		while (ft_isdigit(format[*i]))
			(*i)++;
}

static void	sprint_precision(const char *format, size_t *i, t_sformat *f)
{
	if (f->precision >= 0)
	{
		strcpy_char_record(f, '.', 1);
		(*i)++;
		strcpy_nbr_record(f, f->precision, "0123456789");
		if (format[*i] == '*')
			(*i)++;
		else
			while (ft_isdigit(format[*i]))
				(*i)++;
	}
	else if (f->precision == NEGATIVE_PRECISION)
		(*i) += 2;
}
