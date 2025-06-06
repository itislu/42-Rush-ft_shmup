/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:03:34 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 00:25:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"
#include "libft.h"
#include <stddef.h>
#include <sys/param.h>

static size_t	effective_size(size_t target, size_t available);
static void		record(t_sformat *f, size_t target, size_t actual);

void	strcpy_record(t_sformat *f, const char *src, size_t target_len)
{
	const size_t	available = f->size - f->sprinted;
	const size_t	maxlen = effective_size(target_len, available);
	size_t			actual;
	char			*dest;

	actual = 0;
	if (available > 0)
	{
		dest = &f->str[f->sprinted];
		actual = ft_strlcpy(dest, src, maxlen + 1);
		actual = MIN(actual, maxlen);
	}
	record(f, target_len, actual);
}

void	strcpy_char_record(t_sformat *f, unsigned char c, size_t target_amount)
{
	const size_t	available = f->size - f->sprinted;
	const size_t	amount = effective_size(target_amount, available);
	char			*dest;

	if (available > 0)
	{
		dest = &f->str[f->sprinted];
		ft_memset(dest, c, amount);
		dest[amount] = '\0';
	}
	record(f, target_amount, amount);
}

void	strcpy_nbr_record(t_sformat *f, long nbr, const char *base)
{
	const size_t	available = f->size - f->sprinted;
	unsigned int	nbr_len;
	char			*dest;

	dest = &f->str[f->sprinted];
	nbr_len = ft_strlcpy_nbr_base(dest, nbr, base, available);
	record(f, nbr_len, effective_size(nbr_len, available));
}

static size_t	effective_size(size_t target, size_t available)
{
	if (available == 0)
		return (0);
	return (MIN(target, available - 1));
}

static void	record(t_sformat *f, size_t target, size_t actual)
{
	f->sprinted += actual;
	f->chars_needed += target;
}
