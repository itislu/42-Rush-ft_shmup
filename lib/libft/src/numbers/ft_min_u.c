/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:16:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/param.h>

/**
 * The ft_min_u function returns the minimum of two unsigned integers in a 
 * type-safe way.
 *
 * @param a    The first unsigned integer to compare.
 * @param b    The second unsigned integer to compare.
 *
 * @return     Returns the smaller of the two unsigned integers.
 *
 * @note       If performance is critical, use the MIN macro from sys/param.h 
 *             directly to avoid the function call overhead.
 *             However, when using the macro watch out for double-evaluation and 
 *             type safety!
 */
size_t	ft_min_u(size_t a, size_t b)
{
	return (MIN(a, b));
}
