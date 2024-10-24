/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:28 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/24 15:53:29 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_functions.h"

// ft_echo requires all quotes, $ARGs to be handled beforehand
// ft_echo will take in its given flag, then print its input
// flag input of 0 is no flag and flag input of 1 is -n flag

int	ft_echo(int flag, char *input)
{
	int		i;

	i = 0;
	if (flag > 1 || flag < 0)
		return (db_error("ft_echo recieved an invalid flag", 0));
	if (!input)
		return (db_error("ft_echo recieved a NULL input string", 0));
	printf("%s", input);
	if (flag == 0)
		printf("\n");
	return (1);
}
