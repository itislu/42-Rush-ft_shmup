/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:16 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/05 07:13:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <stddef.h>

int	return_value(size_t ret)
{
	if (ret == (size_t)-1)
	{
		errno = EINVAL;
		return (-1);
	}
	if (ret > INT_MAX)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	return ((int)ret);
}
