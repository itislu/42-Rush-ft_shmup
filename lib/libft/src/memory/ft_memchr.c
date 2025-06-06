/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:13 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 21:50:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*casted_ptr_s = (const unsigned char *)s;
	const unsigned char	casted_c = (unsigned char)c;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (casted_ptr_s[i] == casted_c)
			return ((void *)&casted_ptr_s[i]);
		i++;
	}
	return (NULL);
}
