/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:48:11 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/27 15:48:28 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	db_error(char *error_message, int error_code)
{
	write(2, BOLDRED"Error\n"LINERED, 5 + sizeof(BOLDRED) + sizeof(LINERED));
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n"RESET, sizeof(RESET));
	return (error_code);
}

// int	main(void)
// {
// 	ft_printf("Hello\n");
// 	return (db_error("code broke wowoowowow", 0));
// }
