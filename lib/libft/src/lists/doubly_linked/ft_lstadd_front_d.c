/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:18 by ldulling          #+#    #+#             */
/*   Updated: 2025/06/06 16:24:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * Can prepend a whole list, not just one node.
 */
void	ft_lstadd_front_d(t_list_d **lst, t_list_d *node)
{
	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		ft_lstadd_back_d(&node, *lst);
		*lst = node;
	}
}
