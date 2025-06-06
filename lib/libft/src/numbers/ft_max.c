/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:02:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/10 13:24:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>

/**
 * The ft_max function returns the maximum of two signed integers in a type-safe 
 * way.
 *
 * @param a    The first integer to compare.
 * @param b    The second integer to compare.
 *
 * @return     Returns the larger of the two integers.
 *
 * @note       If performance is critical, use the MAX macro from sys/param.h 
 *             directly to avoid the function call overhead.
 *             However, when using the macro watch out for double-evaluation and 
 *             type safety!
 */
long	ft_max(long a, long b)
{
	return (MAX(a, b));
}
