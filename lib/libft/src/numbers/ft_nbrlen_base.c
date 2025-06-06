/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:56:02 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/05 23:16:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/**
 * The ft_nbrlen_base function calculates the number of digits needed to 
 * represent a signed integer in a given base.
 *
 * @param nbr     The signed number to count the digits of.
 * @param base    The base of the number system (e.g., 10 for decimal, 16 for
 *                hex).
 *
 * @return        Returns the number of digits as an unsigned integer.
 *                Returns 0 if base is 0.
 */
unsigned int	ft_nbrlen_base(long nbr, unsigned int base)
{
	unsigned int	len;

	len = ft_nbrlen_base_u(ft_labs_u(nbr), base);
	if (nbr < 0)
		len++;
	return (len);
}
