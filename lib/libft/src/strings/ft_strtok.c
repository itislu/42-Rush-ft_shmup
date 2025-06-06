/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:48:31 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:46:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * The ft_strtok function breaks a string into a series of tokens using the
 * delimiter string. Each call to ft_strtok returns the next token.
 *
 * @param str      The string to be tokenized. On the first call to ft_strtok,
 *                 this should be the string you want to tokenize. On subsequent
 *                 calls, it should be NULL.
 * @param delim    The delimiter string. Each character in this string is
 *                 considered a valid delimiter.
 *
 * @return         On success, it returns a pointer to the next token in the
 *                 string.
 *                 If there are no more tokens, it returns NULL.
 *
 * @note           Calling ft_strtok the first time with str equal to NULL, or
 *                 at any point with delim equal to NULL, is undefined behavior
 *                 (mirrors the behavior of the original strtok).
 */
char	*ft_strtok(char *str, const char *delim)
{
	static char	*to_parse;
	char		*result;

	if (str != NULL)
		to_parse = str;
	while (*to_parse != '\0' && ft_strchr(delim, *to_parse) != NULL)
		to_parse++;
	result = to_parse;
	while (*to_parse != '\0' && ft_strchr(delim, *to_parse) == NULL)
		to_parse++;
	if (*to_parse != '\0')
	{
		*to_parse = '\0';
		to_parse++;
	}
	if (*result != '\0')
		return (result);
	return (NULL);
}
