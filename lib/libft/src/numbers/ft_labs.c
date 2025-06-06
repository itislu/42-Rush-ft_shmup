/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:16:45 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 22:50:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_labs function calculates the absolute value of a long signed integer.
 *
 * @param j    The long signed integer to get the absolute value of.
 *
 * @return     Returns the absolute value as a long signed integer.
 *
 * @note       Calling ft_labs with j equal to LONG_MIN is undefined behavior
 *             (mirrors the behavior of the original labs).
 */
long	ft_labs(long j)
{
	if (j < 0)
		return (-j);
	return (j);
}
