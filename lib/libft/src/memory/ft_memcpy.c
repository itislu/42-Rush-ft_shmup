/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:20 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/05 00:44:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * The ft_memcpy function copies n bytes from memory area src to memory area
 * dest.
 * The memory areas must not overlap.
 *
 * @param dest    The memory area to copy to.
 * @param src     The memory area to copy from.
 * @param n       The number of bytes to copy.
 *
 * @return        Returns a pointer to dest.
 *
 * @note          Calling ft_memcpy with dest or src equal to NULL with n not 0
 *                is undefined behavior (mirrors the behavior of the original 
 *                memcpy).
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*casted_ptr_src = (const unsigned char *)src;
	unsigned char		*casted_ptr_dest;
	size_t				i;

	casted_ptr_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		casted_ptr_dest[i] = casted_ptr_src[i];
		i++;
	}
	return (dest);
}
