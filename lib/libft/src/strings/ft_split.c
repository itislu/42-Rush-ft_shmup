/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:17 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/13 02:43:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_strings(const char *s, char c);
static void		skip_c(const char *s, size_t *pos, char c);
static size_t	strclen(const char *s, size_t *pos, char c);
static bool		protected_malloc(char **str_array, size_t i, size_t len);

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	pos;
	size_t	str_count;
	char	**str_array;

	str_count = count_strings(s, c);
	str_array = (char **)malloc((str_count + 1) * sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < str_count)
	{
		skip_c(s, &pos, c);
		len = strclen(s, &pos, c);
		if (!protected_malloc(str_array, i, len + 1))
			return (NULL);
		str_array[i] = ft_memcpy(str_array[i], &s[pos - len], len);
		str_array[i][len] = '\0';
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}

static size_t	count_strings(const char *s, char c)
{
	size_t	pos;
	size_t	str_count;

	if (s == NULL)
		return (0);
	str_count = 0;
	pos = 0;
	while (s[pos] != '\0')
	{
		skip_c(s, &pos, c);
		if (s[pos] != '\0')
		{
			str_count++;
			while (s[pos] != c && s[pos] != '\0')
				pos++;
		}
	}
	return (str_count);
}

static void	skip_c(const char *s, size_t *pos, char c)
{
	while (s[*pos] == c)
		(*pos)++;
}

static size_t	strclen(const char *s, size_t *pos, char c)
{
	size_t	len;

	len = 0;
	while (s[*pos] != c && s[*pos] != '\0')
	{
		len++;
		(*pos)++;
	}
	return (len);
}

static bool	protected_malloc(char **str_array, size_t i, size_t len)
{
	str_array[i] = (char *)malloc(len);
	if (str_array[i] == NULL)
	{
		while (i > 0)
			free(str_array[--i]);
		free((void *)str_array);
		return (false);
	}
	return (true);
}
