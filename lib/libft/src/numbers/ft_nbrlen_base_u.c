/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:04:25 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/12 21:03:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * The ft_nbrlen_base_u function calculates the number of digits needed to 
 * represent an unsigned integer in a given base.
 *
 * @param nbr     The unsigned number to count the digits of.
 * @param base    The base of the number system (e.g., 10 for decimal, 16 for
 *                hex).
 *
 * @return        Returns the number of digits as an unsigned integer.
 *                Returns 0 if base is 0.
 */
unsigned int	ft_nbrlen_base_u(size_t nbr, unsigned int base)
{
	unsigned int	len;

	if (base == 0)
		return (0);
	if (nbr == 0)
		return (1);
	len = 0;
	while (nbr != 0)
	{
		len++;
		nbr /= base;
	}
	return (len);
}
