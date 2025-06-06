/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labs_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:16:45 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 23:04:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_labs_u function calculates the absolute value of a long signed 
 * integer.
 *
 * @param j    The long signed integer to get the absolute value of.
 *
 * @return     Returns the absolute value as a long unsigned integer.
 *
 * @note       Because for LONG_MIN the absolute value would exceed LONG_MAX in
 *             two's complement, the return type is unsigned.
 */
unsigned long	ft_labs_u(long j)
{
	if (j < 0)
		return (-(unsigned long)j);
	return (j);
}
