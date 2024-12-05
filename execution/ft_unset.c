/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:34:17 by dbozic            #+#    #+#             */
/*   Updated: 2024/10/23 13:45:30 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_unset2(t_envs *envs, t_envs *prev, t_envs *env)
{
	free(env->contents);
	free(env->name);
	env->contents = NULL;
	env->name = NULL;
	if (!prev)
	{
		prev = envs;
		envs = envs->next;
		free(prev);
	}
	else
	{
		prev->next = env->next;
		free(env);
	}
}

// ft_unset takes in a var_name str, and an initialized *envs list,
//  then unsets the variable under the var_name.
// ft_unset returns 0 upon error and 1 upon success.
// ft_unset will not print an error if the name given through var_name,
//  does not exist in the *envs list.
int	ft_unset(char *var_name, t_envs *envs)
{
	t_envs	*env;
	t_envs	*prev;

	if (!var_name)
		return (db_error("ft_unset recieved NULL var_name", 0));
	env = NULL;
	env = find_in_env_list(var_name, envs);
	if (!env)
		return (0);
	env = envs;
	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, var_name))
			break ;
		prev = env;
		env = env->next;
	}
	ft_unset2(envs, prev, env);
	if (unsetenv(var_name) != 0)
		return (db_error("unsetenv fail in ft_unset", 0));
	return (1);
}
