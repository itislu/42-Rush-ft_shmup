/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:06:25 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/03 00:54:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "_get_next_line.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static bool	check_for_full_leftover_line(t_buf **head, char **result);
static bool	read_until_endofline(t_buf **head, int fd);
static char	*copy_into_result_and_move_head_to_tail(t_buf **head);

char	*get_next_line(int fd)
{
	static t_buf	*head;
	char			*result;

	if (!initial_check(fd, &head))
		return (free_list(&head), NULL);
	if (head->bytes_unsaved != 0)
	{
		if (check_for_full_leftover_line(&head, &result))
			return (result);
		if (!add_new_node(head))
			return (free_list(&head), NULL);
	}
	if (!read_until_endofline(&head, fd))
		return (NULL);
	result = copy_into_result_and_move_head_to_tail(&head);
	if (result == NULL)
		return (NULL);
	head->bytes_unsaved -= head->line_end + 1;
	if (head->bytes_unsaved == 0)
		free_list(&head);
	return (result);
}

static bool	check_for_full_leftover_line(t_buf **head, char **result)
{
	const ssize_t	new_line_end = find_endofline(*head);
	ssize_t			i;
	ssize_t			result_size;

	if (new_line_end == NO_NL)
		return (false);
	result_size = new_line_end - (*head)->line_end;
	*result = (char *)malloc(result_size + 1);
	if (*result == NULL)
		return (free_list(head), true);
	i = 0;
	(*head)->line_end++;
	while (i < result_size)
		(*result)[i++] = (*head)->buf[(*head)->line_end++];
	(*result)[i] = '\0';
	(*head)->bytes_unsaved -= result_size;
	if ((*head)->bytes_unsaved != 0)
		(*head)->line_end = new_line_end;
	else
		free_list(head);
	return (true);
}

static bool	read_until_endofline(t_buf **head, int fd)
{
	t_buf	*cur;

	if ((*head)->next != NULL)
		cur = (*head)->next;
	else
		cur = *head;
	while (cur != NULL)
	{
		cur->bytes_unsaved = read(fd, cur->buf, BUFFER_SIZE);
		if (cur->bytes_unsaved == -1 || (*head)->bytes_unsaved == 0)
			return (free_list(head), false);
		if (cur->bytes_unsaved != BUFFER_SIZE)
			cur->endoffile = true;
		cur->buf[cur->bytes_unsaved] = '\0';
		cur->line_end = find_endofline(cur);
		if (cur->line_end == NO_NL && !cur->endoffile)
			if (!add_new_node(cur))
				return (free_list(head), false);
		cur = cur->next;
	}
	return (true);
}

static char	*copy_into_result_and_move_head_to_tail(t_buf **head)
{
	t_buf	*cur;
	char	*result;
	size_t	i;
	ssize_t	j;

	result = (char *)malloc(count_result_size(*head) + 1);
	if (result == NULL)
		return (free_list(head), NULL);
	i = 0;
	while ((*head)->next != NULL)
	{
		cur = *head;
		(*head) = (*head)->next;
		j = cur->line_end + 1;
		while (cur->buf[j] != '\0')
			result[i++] = cur->buf[j++];
		free(cur);
	}
	j = 0;
	while (j <= (*head)->line_end)
		result[i++] = (*head)->buf[j++];
	result[i] = '\0';
	return (result);
}
