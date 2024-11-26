/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:54:11 by dbozic            #+#    #+#             */
/*   Updated: 2024/10/23 13:54:23 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// ft_env will print all environmental variables tracked by envs.
// ft_env returns 0 upon error and 1 upon success, however errors,
//  shouldnt happen if the *envs list is initialized and used properly.
int	ft_env(t_envs *envs)
{
	t_envs	*current;

	if (!envs)
		return (db_error("ft_env recieved a NULL env list", 0));
	current = envs;
	while (current)
	{
		if ((!current->name) || (!current->contents))
			return (db_error("ft_env found NULL content in the env list", 0));
		printf("%s=%s\n", current->name, current->contents);
		current = current->next;
	}
	return (1);
}
