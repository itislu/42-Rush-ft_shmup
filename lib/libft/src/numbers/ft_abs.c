/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:16:45 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 21:21:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_abs function calculates the absolute value of a signed integer.
 *
 * @param j    The signed integer to get the absolute value of.
 *
 * @return     Returns the absolute value as a signed integer.
 *
 * @note       Calling ft_abs with j equal to INT_MIN is undefined behavior
 *             (mirrors the behavior of the original abs).
 */
int	ft_abs(int j)
{
	if (j < 0)
		return (-j);
	return (j);
}
