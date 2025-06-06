/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:16:45 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 23:05:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_abs_u function calculates the absolute value of a signed integer.
 *
 * @param j    The signed integer to get the absolute value of.
 *
 * @return     Returns the absolute value as an unsigned integer.
 *
 * @note       Because for INT_MIN the absolute value would exceed INT_MAX in
 *             two's complement, the return type is unsigned.
 */
unsigned int	ft_abs_u(int j)
{
	if (j < 0)
		return (-(unsigned int)j);
	return (j);
}
