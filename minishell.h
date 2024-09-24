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

# define RESET   		"\033[0m"
# define RED     		"\033[31m"
# define GREEN   		"\033[32m"
# define YELLOW  		"\033[33m"
# define BLUE    		"\033[34m"
# define MAGENTA 		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"

# define BOLD	 		"\033[1m"
# define BOLDRED     	"\033[1;31m"
# define BOLDGREEN   	"\033[1;32m"
# define BOLDYELLOW  	"\033[1;33m"
# define BOLDBLUE    	"\033[1;34m"
# define BOLDMAGENTA 	"\033[1;35m"
# define BOLDCYAN		"\033[1;36m"
# define BOLDWHITE		"\033[1;37m"

# define LINE			"\033[4m]"
# define LINERED     	"\033[4;31m"
# define LINEGREEN   	"\033[4;32m"
# define LINEYELLOW  	"\033[4;33m"
# define LINEBLUE    	"\033[4;34m"
# define LINEMAGENTA 	"\033[4;35m"
# define LINECYAN		"\033[4;36m"
# define LINEWHITE		"\033[4;37m"

# define FLASH   		"\033[5m"
# define FLASHRED     	"\033[5;31m"
# define FLASHGREEN   	"\033[5;32m"
# define FLASHYELLOW  	"\033[5;33m"
# define FLASHBLUE    	"\033[5;34m"
# define FLASHMAGENTA 	"\033[5;35m"
# define FLASHCYAN		"\033[5;36m"
# define FLASHWHITE		"\033[5;37m"

# define FILLBLACK   	"\033[40m"
# define FILLRED     	"\033[41m"
# define FILLGREEN   	"\033[42m"
# define FILLYELLOW  	"\033[43m"
# define FILLBLUE    	"\033[44m"
# define FILLMAGENTA 	"\033[45m"
# define FILLCYAN		"\033[46m"
# define FILLWHITE		"\033[47m"

# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"


#endif