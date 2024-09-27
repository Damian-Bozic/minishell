/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:53:55 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/24 15:53:58 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_FUNCTIONS_H
# define BUILT_IN_FUNCTIONS_H

# include "../minishell.h"
# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 8192
# endif

int	ft_pwd(void);
int	ft_echo(int flag, char *input);
int	ft_cd(char *input);

#endif