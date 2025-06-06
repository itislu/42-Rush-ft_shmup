/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:52:20 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:10:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_lstswap_head function swaps the first two nodes of a singly linked
 * list.
 *
 * @param lst    A double pointer to the first node of the list.
 *
 * @note         The function does nothing if the list is empty or contains only
 *               one node.
 */
void	ft_lstswap_head(t_list **lst)
{
	t_list	*new_head;

	if (lst == NULL || *lst == NULL || (*lst)->next == NULL)
		return ;
	new_head = (*lst)->next;
	(*lst)->next = new_head->next;
	new_head->next = *lst;
	*lst = new_head;
}
