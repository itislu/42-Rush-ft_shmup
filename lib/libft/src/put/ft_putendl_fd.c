/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:07 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:12:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1 || write(fd, "\n", 1) == -1)
		return ;
}
