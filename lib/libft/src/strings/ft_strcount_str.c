/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 02:10:13 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/04 05:27:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_strcount_str function counts non-overlapping occurrences of the string
 * little within the string big.
 *
 * @param big       The string to be searched within.
 * @param little    The string to search for.
 *
 * @return          Returns the number of non-overlapping occurrences of little
 *                  in big. Returns 0 if either string is NULL, empty, or if
 *                  little is not found in big.
 *
 * @note            After finding an occurrence, the function advances past the
 *                  entire matched substring before continuing the search, which
 *                  means overlapping matches are not counted.
 */
size_t	ft_strcount_str(const char *big, const char *little)
{
	size_t	count;
	size_t	little_len;

	if (big == NULL || little == NULL || *big == '\0' || *little == '\0')
		return (0);
	count = 0;
	little_len = ft_strlen(little);
	while (*big != '\0')
	{
		if (ft_strncmp(big, little, little_len) == 0)
		{
			count++;
			big += little_len;
		}
		else
			big++;
	}
	return (count);
}
