/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:45:20 by dbozic            #+#    #+#             */
/*   Updated: 2024/10/23 13:45:22 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_functions.h"

static t_envs	*new_env(char *var_name, char *contents)
{
	t_envs	*new;

	new = malloc(sizeof(t_envs));
	if (!new)
		return (NULL);
	new->name = var_name;
	new->contents = contents;
	new->next = NULL;
	return (new);
}

static int	ft_export2(t_envs *cur, t_envs *envs, char *var_name, char *cont)
{
	cur = envs;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new_env(var_name, cont);
	if (!cur->next)
	{
		free(var_name);
		free(cont);
		return (db_error("malloc fail in ft_export", 0));
	}
	if (setenv(var_name, cont, 1) == 0)
		return (1);
	free(var_name);
	free(cont);
	free(cur->next);
	cur->next = NULL;
	return (db_error("setenv error in ft_export", 0));
}

// ft_export takes in an already allocated *var_name and *contents variables,
//  aswell as an initiated envs list, and either overwrites or creates a new,
//  environmental variable.
// ft_export will return 0 upon error, and 1 upon success.
// upon error ft_export will free *var_name and *contents, but not *env.
int	ft_export(char *var_name, char *contents, t_envs *envs)
{
	t_envs	*current;

	if (!envs)
		return (db_error("ft_export recieved a NULL envs variable", 0));
	if (!contents)
		return (db_error("ft_export recieved a NULL contents variable", 0));
	if (!var_name)
		return (db_error("ft_export recieved a NULL var_name variable", 0));
	current = find_in_env_list(var_name, envs);
	if (!current)
		return (ft_export2(current, envs, var_name, contents));
	free(current->contents);
	free(current->name);
	if (setenv(var_name, contents, 1) == 0)
	{
		current->contents = contents;
		current->name = var_name;
		return (1);
	}
	return (db_error("setenv error in ft_export", 0));
}
