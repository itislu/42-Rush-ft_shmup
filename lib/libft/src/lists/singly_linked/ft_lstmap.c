/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:35 by ldulling          #+#    #+#             */
/*   Updated: 2025/05/28 21:24:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

t_list	*ft_lstmap(const t_list *lst, void *(*f)(const void *), \
					void (*del)(void *))
{
	const t_list	*cur = lst;
	t_list			*new_lst;
	t_list			*new_lst_tail;
	t_list			*new_node;
	void			*new_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	new_lst_tail = NULL;
	while (cur != NULL)
	{
		new_content = (*f)(cur->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back_tail(&new_lst, &new_lst_tail, new_node);
		cur = cur->next;
	}
	return (new_lst);
}
