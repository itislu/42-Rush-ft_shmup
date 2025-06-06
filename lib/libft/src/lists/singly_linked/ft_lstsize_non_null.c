/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_non_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:52:32 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/04 04:04:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_lstsize_non_null function counts the number of non-NULL content nodes
 * in a singly linked list.
 *
 * @param lst    A pointer to the first node of the list.
 *               If lst is NULL, the function returns 0.
 *
 * @return       The number of non-NULL content nodes in the list.
 */
int	ft_lstsize_non_null(const t_list *lst)
{
	const t_list	*cur = lst;
	int				n;

	n = 0;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			n++;
		cur = cur->next;
	}
	return (n);
}
