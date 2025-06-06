/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:06 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 18:46:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_lstsize_d(const t_list_d *lst)
{
	const t_list_d	*cur = lst;
	int				n;

	n = 0;
	while (cur != NULL)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}
