/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf_shared.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:27:27 by ldulling          #+#    #+#             */
/*   Updated: 2025/02/05 07:13:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_SHARED_H
# define _FT_PRINTF_SHARED_H

# include <stddef.h>

# define SPECIFIERS				"cspdiuxX%"
# define FLAGS					"#+- 0"
# define NULL_PRINTOUT_PTR		"(nil)"
# define NULL_PRINTOUT_STR		"(null)"
# define FROM_NEGATIVE_WIDTH	2
# define NO_PRECISION_SET		-1
# define NEGATIVE_PRECISION		-2

int	return_value(size_t ret);

#endif
