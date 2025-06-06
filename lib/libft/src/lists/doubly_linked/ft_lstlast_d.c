/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:32 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 10:09:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

t_list_d	*ft_lstlast_d(t_list_d *lst)
{
	t_list_d	*cur;

	if (lst == NULL)
		return (NULL);
	cur = lst;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}
