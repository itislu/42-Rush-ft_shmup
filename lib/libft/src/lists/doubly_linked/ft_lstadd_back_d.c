/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:12 by ldulling          #+#    #+#             */
/*   Updated: 2025/06/06 16:24:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * Does not mark the new node as the end of the list by itself.
 * Therefore, a whole list can be appended, not just one node.
 */
void	ft_lstadd_back_d(t_list_d **lst, t_list_d *node)
{
	t_list_d	*cur;

	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		cur = *lst;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = node;
		node->prev = cur;
	}
}
