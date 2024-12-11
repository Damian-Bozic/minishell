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

#include "execution.h"

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

char *set_var_name(char *arg)
{
	int		i;
	char	*rtn;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	rtn = malloc(i + 1);
	if (!rtn)
		return (NULL);
	rtn[i] = 0;
	ft_strlcpy(rtn, arg, i + 1);
	return (rtn);
}

char *set_contents(char *arg)
{
	int	i;

	i = 0;
	char *rtn;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	rtn = malloc (ft_strlen(&arg[i + 1]) + 1);
	if (!rtn)
		return (NULL);
	ft_strlcpy(rtn, &arg[i + 1], ft_strlen(&arg[i]));
	return (rtn);
}

// ft_export takes in an argv array aswell as an envs list, 
//  and either overwrites or creates a new environmental variable.
// ft_export will return 0 upon error, and 1 upon success.
// ft_export will NOT free **argv nor *envs.
int	ft_export(char **argv, t_envs *envs)
{
	t_envs	*current;
	char	*var_name;
	char	*contents;

	// remake to include frees for contents and var_name
	if (!envs || !argv || !argv[0] || !argv[1] || argv[2])
		return (db_error("ft_export NULL or invalid input", 0));
	var_name = set_var_name(argv[1]);
	if (!var_name)
		return (0);
	contents = set_contents(argv[1]);
	if (!contents)
	{
		free(var_name);
		return (0);
	}
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
