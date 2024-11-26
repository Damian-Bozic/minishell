/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:15:20 by dbozic            #+#    #+#             */
/*   Updated: 2024/11/26 20:15:24 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strjoin_mod(char *alstr, char *str, size_t s1_n, size_t s2_n)
{
	size_t		i;
	size_t		j;
	char		*rtn;

	i = 0;
	j = 0;
	rtn = malloc(s1_n + s2_n + 1);
	if (!rtn)
		free(alstr);
	if (!rtn)
		return (NULL);
	while (i < s1_n)
	{
		rtn[i] = alstr[i];
		i++;
	}
	while (j < s2_n)
	{
		rtn[i + j] = str[j];
		j++;
	}
	rtn[i + j] = '\0';
	free(alstr);
	alstr = NULL;
	return (rtn);
}
