/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:02:46 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/19 15:02:50 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This is the main .h file

#ifndef MINISHELL_H
# define MINISHELL_H
# define RESET   	"\033[0m"
# define RED     	"\033[31m"
# define GREEN   	"\033[32m"
# define YELLOW  	"\033[33m"
# define BLUE    	"\033[34m"
# define MAGENTA 	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"


#endif