/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:02:33 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/10 20:22:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			bytes;

	if (!ft_inrange_mul_u(nmemb, size, SIZE_MAX))
	{
		errno = ENOMEM;
		return (NULL);
	}
	bytes = nmemb * size;
	ptr = (unsigned char *)malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bytes);
	return ((void *)ptr);
}
