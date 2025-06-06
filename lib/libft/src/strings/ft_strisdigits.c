/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:22 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/02 14:21:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_strisdigits function checks if the string s contains digits ONLY and
 * has at least one digit.
 *
 * @param s    The string to check.
 *
 * @return     Returns true if the string s contains digits and digits only, 
 *             false otherwise.
 */
bool	ft_strisdigits(const char *s)
{
	const unsigned char	*casted_ptr_s;

	if (s == NULL || *s == '\0')
		return (false);
	casted_ptr_s = (const unsigned char *)s;
	while (ft_isdigit(*casted_ptr_s))
		casted_ptr_s++;
	if (*casted_ptr_s != '\0')
		return (false);
	return (true);
}
