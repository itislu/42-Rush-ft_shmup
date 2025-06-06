/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:14:59 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/05 00:45:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * The ft_strdup function duplicates the string pointed to by s.
 *
 * @param s    A pointer to the string to be duplicated.
 *
 * @return     A pointer to the newly allocated string, or NULL if the
 *             allocation failed.
 *             The returned string will have to be freed later.
 *
 * @note       Calling ft_strdup with s equal to NULL is undefined behavior
 *             (mirrors the behavior of the original strdup).
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, len);
	return (dup);
}
