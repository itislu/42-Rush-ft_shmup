/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_nbr_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:20:16 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 23:17:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static size_t			get_base_len(const char *base);
static bool				has_duplicates(const char *base, size_t base_len);
static unsigned long	truncate_nbr_if_needed(unsigned long nbr, \
												size_t base_len, size_t size);
static size_t			strcpy_nbr(char *dst, unsigned long u_nbr, \
									const char *base, size_t base_len);

/**
 * The ft_strlcpy_nbr_base function converts a number to a given base and copies
 * it to a string, truncating the least significant digits if needed.
 * The given base will be checked for validity.
 * It will then NUL-terminate the result, unless size is 0.
 *
 * @param dst     The string to copy to.
 * @param nbr     The number to convert and copy.
 * @param base    The string containing all characters to be used for the 
 *                conversion.
 *                Must contain at least 2 unique characters, no duplicates, and 
 *                no '+' or '-' signs.
 * @param size    The total size of dst, including the space for the
 *                NUL-terminator.
 *
 * @return        The total length the number would have in the given base,
 *                including the minus sign if negative.
 *                Returns 0 if the base is invalid.
 *                If the return value is >= size, the output string has been
 *                truncated.
 *
 * @note          Calling ft_strlcpy_nbr_base with dst equal to NULL with a size
 *                not 0 is undefined behavior (mirrors the behavior of the 
 *                original basic strlcpy).
 */
size_t	ft_strlcpy_nbr_base(char *dst, long nbr, const char *base, size_t size)
{
	const size_t	base_len = get_base_len(base);
	unsigned long	u_nbr;
	size_t			copied;

	if (base_len < 2 || has_duplicates(base, base_len))
		return (0);
	copied = 0;
	if (nbr < 0 && copied + 1 < size)
		dst[copied++] = '-';
	if (copied + 1 < size)
	{
		u_nbr = ft_labs_u(nbr);
		u_nbr = truncate_nbr_if_needed(u_nbr, base_len, size - copied - 1);
		copied += strcpy_nbr(&dst[copied], u_nbr, base, base_len);
	}
	if (size > 0)
		dst[copied] = '\0';
	return (ft_nbrlen_base(nbr, base_len));
}

static size_t	get_base_len(const char *base)
{
	size_t	base_len;

	if (base == NULL)
		return (0);
	base_len = 0;
	while (base[base_len] != '\0')
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return (0);
		base_len++;
	}
	return (base_len);
}

static bool	has_duplicates(const char *base, size_t base_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < base_len - 1)
	{
		j = i + 1;
		while (j < base_len)
		{
			if (base[i] == base[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static unsigned long	truncate_nbr_if_needed(unsigned long nbr, \
												size_t base_len, size_t size)
{
	size_t	nbr_len;

	nbr_len = ft_nbrlen_base_u(nbr, base_len);
	while (nbr_len > size)
	{
		nbr /= base_len;
		nbr_len--;
	}
	return (nbr);
}

static size_t	strcpy_nbr(char *dst, unsigned long u_nbr, const char *base, \
							size_t base_len)
{
	size_t	copied;

	copied = 0;
	if (u_nbr >= base_len)
		copied += strcpy_nbr(&dst[copied], u_nbr / base_len, base, base_len);
	u_nbr %= base_len;
	dst[copied++] = base[u_nbr];
	return (copied);
}
