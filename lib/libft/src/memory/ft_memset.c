/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:11:59 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 21:54:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	const unsigned char	casted_c = (unsigned char)c;
	unsigned char		*casted_ptr_s;
	size_t				i;

	casted_ptr_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		casted_ptr_s[i] = casted_c;
		i++;
	}
	return (s);
}
