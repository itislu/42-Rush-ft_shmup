/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:21 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 01:55:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>

static void	set_flags(const char *format, size_t *i, t_sformat *f);
static void	set_width(const char *format, size_t *i, t_sformat *f, va_list *ap);
static void	set_precision(const char *format, size_t *i, t_sformat *f, \
							va_list *ap);
static void	set_specifier(const char *format, size_t *i, t_sformat *f);

size_t	set_sformat(const char *format, size_t *i, t_sformat *f, va_list *ap)
{
	const size_t	i_original = *i;

	if (format[*i] != '\0')
	{
		set_flags(format, i, f);
		if (format[*i] != '\0')
		{
			set_width(format, i, f, ap);
			if (format[*i] != '\0')
			{
				set_precision(format, i, f, ap);
				if (format[*i] != '\0')
					set_specifier(format, i, f);
			}
		}
	}
	return (*i - i_original);
}

static void	set_flags(const char *format, size_t *i, t_sformat *f)
{
	while (true)
	{
		if (format[*i] == '#')
			f->hash = true;
		else if (format[*i] == '+')
			f->plus = true;
		else if (format[*i] == ' ')
			f->space = true;
		else if (format[*i] == '-')
			f->minus = 1;
		else if (format[*i] == '0')
			f->zero = true;
		else
			return ;
		(*i)++;
	}
}

static void	set_width(const char *format, size_t *i, t_sformat *f, va_list *ap)
{
	int	nbr;

	nbr = 0;
	if (format[*i] == '*')
	{
		nbr = va_arg(*ap, int);
		if (nbr < 0)
		{
			if (!f->minus)
				f->minus = FROM_NEGATIVE_WIDTH;
			nbr *= -1;
		}
		(*i)++;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			nbr = nbr * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	f->width = nbr;
}

static void	set_precision(const char *format, size_t *i, t_sformat *f, \
							va_list *ap)
{
	int	nbr;

	if (format[*i] != '.')
		return ;
	nbr = 0;
	(*i)++;
	if (format[*i] == '*')
	{
		nbr = va_arg(*ap, int);
		if (nbr < 0)
			nbr = NEGATIVE_PRECISION;
		(*i)++;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			nbr = nbr * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	f->precision = nbr;
}

static void	set_specifier(const char *format, size_t *i, t_sformat *f)
{
	const char	*specifier = ft_strchr(SPECIFIERS, format[*i]);

	if (specifier != NULL)
	{
		f->specifier = *specifier;
		(*i)++;
	}
	else
		f->unresolved = true;
}
