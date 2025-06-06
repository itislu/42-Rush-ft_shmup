/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:03 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:35:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "../_ft_printf_shared.h"
#include <stdarg.h>
#include <stddef.h>

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	size_t		i;
	t_sformat	f;
	va_list		ap_copy;

	if (!check_args(str, size, format))
		return (return_value(-1));
	f.str = str;
	f.size = size;
	f.unresolved = false;
	f.sprinted = 0;
	f.chars_needed = 0;
	i = 0;
	va_copy(ap_copy, ap);
	while (format[i] != '\0' && f.chars_needed != (size_t)-1)
	{
		reset_sformat(&f);
		parseandsprint(format, &i, &f, &ap_copy);
	}
	va_end(ap_copy);
	return (return_value(f.chars_needed));
}
