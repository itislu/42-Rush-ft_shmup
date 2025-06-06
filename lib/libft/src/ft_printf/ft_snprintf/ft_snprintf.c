/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:03 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 00:42:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (ret);
}
