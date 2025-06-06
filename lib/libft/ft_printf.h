/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:08 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/06 20:10:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

int	ft_printf(const char *format, ...) \
		__attribute__((format (printf, 1, 2)));
int	ft_dprintf(int fd, const char *format, ...) \
		__attribute__((format (printf, 2, 3)));
int	ft_snprintf(char *str, size_t size, const char *format, ...) \
		__attribute__((format (printf, 3, 4)));
int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap) \
		__attribute__((format (printf, 3, 0)));

#endif
