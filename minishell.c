/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:02:27 by dbozic            #+#    #+#             */
/*   Updated: 2024/09/19 15:02:39 by dbozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
// In order to make the history and other things to work, we will need to be
// able to detect escape key inputs like arrow keys and ctrl keys

int	main(void)
{
	// char	*input_line;

    // while(*envp)
	// {
    //     printf("%s\n", *envp++);
	// }
	db_error("error check", 0);
	ft_pwd();
	ft_echo(1, "with -n flag");
	ft_echo(0, "without -n flag");
	ft_cd("/nfs/homes");
	ft_pwd();
	ft_cd("/nfs/homes/dbozic");
	ft_pwd();
	ft_cd("/nfs/homes/dbozic/minishell");
	ft_pwd();
	// while (1)
	// {
	// 	input_line = NULL;
	// 	input_line = readline(GREEN"Zabka"CYAN"42: "RESET);
	// 	if (strcmp(input_line, "exit") == 0)
	// 	{
	// 		ft_printf("exiting\n");
	// 		free(input_line);
	// 		break ;
	// 	}
	// 	ft_printf("%s\n", input_line);
	// 	free(input_line);
	// }
}