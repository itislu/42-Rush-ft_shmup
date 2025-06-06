/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:29 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:10:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_lstpop_front function removes the first node from a singly linked list
 * and returns it - like popping a stack.
 *
 * @param lst    A double pointer to the first node of the list.
 *
 * @return       The removed node, or NULL if the list was empty.
 */
t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*popped_node;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	popped_node = *lst;
	*lst = (*lst)->next;
	popped_node->next = NULL;
	return (popped_node);
}
