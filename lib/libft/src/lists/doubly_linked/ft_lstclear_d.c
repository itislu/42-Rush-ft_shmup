/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:22 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:07:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_lstclear_d(t_list_d **lst, void (*del)(void *))
{
	t_list_d	*cur;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdelone_d(cur, del);
	}
}
