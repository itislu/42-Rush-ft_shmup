/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:02:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/10 13:24:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>

/**
 * The ft_min function returns the minimum of two signed integers in a type-safe 
 * way.
 *
 * @param a    The first integer to compare.
 * @param b    The second integer to compare.
 *
 * @return     Returns the smaller of the two integers.
 *
 * @note       If performance is critical, use the MIN macro from sys/param.h 
 *             directly to avoid the function call overhead.
 *             However, when using the macro watch out for double-evaluation and 
 *             type safety!
 */
long	ft_min(long a, long b)
{
	return (MIN(a, b));
}
