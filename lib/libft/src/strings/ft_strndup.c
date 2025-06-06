/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:14:59 by ldulling          #+#    #+#             */
/*   Updated: 2025/06/06 16:11:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * The ft_strndup function duplicates up to n characters from the string pointed
 * to by s. If s is longer than n, only n characters are copied, and a
 * NUL-terminator is added.
 *
 * @param s    A pointer to the string to be duplicated.
 * @param n    The maximum number of characters to be duplicated.
 *
 * @return     A pointer to the newly allocated string, or NULL if the
 *             allocation failed.
 *             The returned string will have to be freed later.
 *
 * @note       Calling ft_strdup with s equal to NULL with n not 0 is undefined 
 *             behavior (mirrors the behavior of the original strndup).
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (n == 0)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
