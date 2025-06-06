/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:27:30 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 18:15:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_format
{
	bool			hash;
	bool			plus;
	bool			space;
	int				minus;
	bool			zero;
	unsigned int	width;
	int				precision;
	char			specifier;
	bool			unresolved;
	int				fd;
}	t_format;

size_t			parseandprint(const char *format, size_t *i, t_format *f, \
								va_list *ap);
size_t			print_argument(const t_format *f, va_list *ap);
unsigned int	print_char(unsigned char c, const t_format *f);
unsigned int	print_nbr(long nbr, const t_format *f);
unsigned int	print_nbr_padding_left(const t_format *f, char padding, \
										unsigned int len_full);
unsigned int	print_nbr_padding_right(const t_format *f, \
										unsigned int len_full);
unsigned int	print_nbr_zero_padding(const t_format *f, unsigned int len_nbr);
size_t			print_parsed(const char *format, size_t parsed, \
								const t_format *f);
unsigned int	print_ptr(size_t ptr, const t_format *f);
unsigned int	print_ptr_padding_left(const t_format *f, \
										unsigned int len_full);
unsigned int	print_ptr_padding_right(const t_format *f, \
										unsigned int len_full);
unsigned int	print_ptr_prefix(const t_format *f);
unsigned int	print_ptr_zero_padding(const t_format *f, \
										unsigned int len_ptr, \
										unsigned int len_full);
size_t			print_str(const char *str, const t_format *f);
void			reset_format(t_format *f);
size_t			set_format(const char *format, size_t *i, t_format *f, \
							va_list *ap);

#endif
