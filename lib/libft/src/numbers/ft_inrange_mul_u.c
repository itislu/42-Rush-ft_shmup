/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inrange_mul_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:36:31 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/05 08:24:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

/**
 * The ft_inrange_mul_u function checks if the multiplication of two size_t 
 * numbers would stay within a given maximum value without causing an overflow.
 *
 * @param a      First unsigned number to multiply.
 * @param b      Second unsigned number to multiply.
 * @param max    Maximum allowed value for the result.
 *
 * @return       Returns true if the multiplication would stay within range,
 *               false if it would exceed max.
 */
bool	ft_inrange_mul_u(size_t a, size_t b, size_t max)
{
	if (a == 0 || b == 0)
		return (true);
	if (a > max / b)
		return (false);
	return (true);
}
