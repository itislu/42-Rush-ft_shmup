/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_down_even.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:56:43 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 11:14:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_round_down_even function rounds down an integer to the nearest even
 * number.
 *
 * If the value is already even, the function returns the value unchanged.
 *
 * @param value    The integer to round down.
 *
 * @return         Returns the nearest even integer less than or equal to the
 *                 input.
 */
int	ft_round_down_even(int value)
{
	return (value & ~1);
}
