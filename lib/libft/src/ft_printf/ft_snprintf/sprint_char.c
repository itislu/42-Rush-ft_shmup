/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:51 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/09 23:32:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_snprintf.h"

static void	sprint_char_padding_left(t_sformat *f);
static void	sprint_char_padding_right(t_sformat *f);

void	sprint_char(unsigned char c, t_sformat *f)
{
	sprint_char_padding_left(f);
	strcpy_char_record(f, c, 1);
	sprint_char_padding_right(f);
}

static void	sprint_char_padding_left(t_sformat *f)
{
	if (!f->minus && f->width > 1)
		strcpy_char_record(f, ' ', f->width - 1);
}

static void	sprint_char_padding_right(t_sformat *f)
{
	if (f->minus && f->width > 1)
		strcpy_char_record(f, ' ', f->width - 1);
}
