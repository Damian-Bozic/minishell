/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:13:43 by dbozic            #+#    #+#             */
/*   Updated: 2024/11/26 20:13:45 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*filter_argv3(char *rtn, char *env, int *i, int j)
{
	char	*rest;

	rest = malloc(ft_strlen(&rtn[*i]));
	if (!rest)
	{
		free(rtn);
		return (NULL);
	}
	ft_strlcpy(rest, &rtn[*i + j + 1], ft_strlen(&rtn[*i + j]));
	rtn[*i] = 0;
	rtn = ft_strjoin_mod(rtn, env, ft_strlen(rtn), ft_strlen(env));
	if (!rtn)
	{
		free(rest);
		return (NULL);
	}
	rtn = ft_strjoin_mod(rtn, rest, ft_strlen(rtn), ft_strlen(rest));
	if (!rtn)
	{
		free(rest);
		return (NULL);
	}
	*i = 0;
	free(rest);
	return (rtn);
}

static char	*filter_argv2(char *rtn, char **envp, int *i, int j)
{
	char	*env;
	char	*temp;

	temp = malloc(j + 1);
	if (!temp)
	{
		free(rtn);
		return (NULL);
	}
	ft_strlcpy(temp, &rtn[*i + 1], j + 1);
	env = ft_getenv(temp, envp);
	free(temp);
	return (filter_argv3(rtn, env, i, j));
}

char	*filter_argv(char *arg, char **envp)
{
	int		i;
	int		j;
	char	*rtn;

	i = 0;
	rtn = ft_strdup(arg);
	if (!rtn)
		return (db_nerror("malloc fail in filter_argv"));
	while (rtn[i])
	{
		if (rtn[i] == '$')
		{
			j = 0;
			while ((rtn[i + j + 1]) && rtn[i + j + 1] != '$'
				&& rtn[i + j + 1] != '/')
				j++;
			rtn = filter_argv2(rtn, envp, &i, j);
			if (!rtn)
				return (db_nerror("malloc fail in filter_argv"));
			printf("rtn = %s\n", rtn);
		}
		i++;
	}
	return (rtn);
}
