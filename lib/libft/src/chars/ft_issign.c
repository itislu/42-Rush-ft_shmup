/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:40 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/29 11:14:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_issign function checks if the passed character is a sign character
 * ('+' or '-').
 *
 * @param c    The character to check.
 *
 * @return     Returns 1 if the character is a sign character, 0 otherwise.
 */
int	ft_issign(int c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}
