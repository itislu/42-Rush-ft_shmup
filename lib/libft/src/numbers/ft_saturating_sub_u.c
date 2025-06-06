/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saturating_sub_u.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:15:14 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/03 22:31:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * The ft_saturating_sub_u function performs an unsigned integer subtraction,
 * saturating at the numeric bound (0) instead of overflowing.
 *
 * @param lhs    The left-hand side operand of the subtraction.
 * @param rhs    The right-hand side operand of the subtraction.
 *
 * @return       Returns the result of lfs - rhs, or 0 if lhs <= rhs.
 */
size_t	ft_saturating_sub_u(size_t lhs, size_t rhs)
{
	if (lhs > rhs)
		return (lhs - rhs);
	return (0);
}
