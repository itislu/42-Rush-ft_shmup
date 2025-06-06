/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isodd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:22:01 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:52:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_isodd function checks if an integer is odd.
 *
 * @param value    The integer to check.
 *
 * @return         Returns true if the integer is odd, false if it is even.
 */
bool	ft_isodd(int value)
{
	return ((value & 1) != 0);
}
