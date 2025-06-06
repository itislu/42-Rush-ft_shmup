/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:12 by ldulling          #+#    #+#             */
/*   Updated: 2025/06/06 16:24:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_lstinsert_after function inserts a new node or even a full linked list
 * after a given node into a singly linked list.
 *
 * @param lst    A double pointer to the node after which the new list should be
 *               inserted.
 *               If *lst is NULL, the new node is set as the first node.
 * @param node   The new node or list to be inserted into the list.
 */
void	ft_lstinsert_after(t_list **lst, t_list *node)
{
	t_list	*old_next;

	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		old_next = (*lst)->next;
		(*lst)->next = node;
		ft_lstlast(node)->next = old_next;
	}
}
