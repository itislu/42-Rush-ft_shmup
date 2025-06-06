/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:06 by ldulling          #+#    #+#             */
/*   Updated: 2025/03/04 04:03:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * The ft_strlen function calculates the length of the string pointed to by s,
 * excluding the terminating NUL byte ('\0').
 *
 * @param s    The string to be measured.
 *
 * @return     The length of the string s.
 *
 * @note       Calling ft_strlen with s equal to NULL is undefined behavior 
 *             (mirrors the behavior of the original strlen).
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
