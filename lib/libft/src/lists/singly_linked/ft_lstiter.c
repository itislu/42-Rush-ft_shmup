/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:29 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:09:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur;

	if (lst == NULL || f == NULL)
		return ;
	cur = lst;
	while (cur != NULL)
	{
		(*f)(cur->content);
		cur = cur->next;
	}
}
