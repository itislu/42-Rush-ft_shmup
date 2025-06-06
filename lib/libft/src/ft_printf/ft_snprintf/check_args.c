/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:45:40 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/12 23:42:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

bool	check_args(char *str, size_t size, const char *format)
{
	if (format != NULL)
		return (true);
	if (size > 0)
		str[0] = '\0';
	return (false);
}
