/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:19 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 19:40:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;
	size_t	len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
