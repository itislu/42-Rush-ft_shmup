/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_next_line.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:27:59 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/04 21:11:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# include "get_next_line.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

# define FD_MAX			1048576
# define NO_NL			-1

typedef struct s_buf
{
	char			buf[BUFFER_SIZE + 1];
	ssize_t			bytes_unsaved;
	ssize_t			line_end;
	bool			endoffile;
	struct s_buf	*next;
}	t_buf;

bool	add_new_node(t_buf *cur);
size_t	count_result_size(t_buf *cur);
ssize_t	find_endofline(t_buf *cur);
void	free_list(t_buf **head);
bool	initial_check(int fd, t_buf **head);

#endif
