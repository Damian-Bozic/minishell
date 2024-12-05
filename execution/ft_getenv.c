/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:22:36 by dbozic            #+#    #+#             */
/*   Updated: 2024/11/26 20:22:38 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_getenv(char *env_name, char **envp)
{
	int		i;
	char	*rtn;

	i = 0;
	rtn = NULL;
	if (!envp)
		return (db_nerror("ft_getenv recieved NULL envp"));
	if (!env_name)
		return (db_nerror("ft_getenv recieved NULL input"));
	while (envp[i])
	{
		if (ft_strncmp(env_name, envp[i], ft_strlen(env_name)) == 0)
		{
			rtn = &envp[i][ft_strlen(env_name) + 1];
			break ;
		}
		i++;
	}
	return (rtn);
}
