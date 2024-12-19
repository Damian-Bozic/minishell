/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasiuk <amasiuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:11 by dbozic            #+#    #+#             */
/*   Updated: 2024/12/16 01:35:22 by amasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mult;

	mult = count * size;
	ptr = malloc(mult);
	if (!ptr || (count != 0 && mult / count != size))
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
// size_t * size_t protection incase your calloc is used at nasa.

/*int	main(void)
{
#include <stdio.h>
#include <stdlib.h>

	int		i;
	char	c;
	int		nmemb = 4;
	int		size = 20;
	char	*ptr;

	write(1, "new1", 4);
	ptr = ft_calloc(nmemb, size);
	i = 0;
	while (i < 40)
	{
		c = ptr[i];
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	write(1, "new2", 4);

	free(ptr);
	i = 0;
	while (i < 40)
	{
		c = ptr[i];
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	write(1, "new3", 4);

	ptr = calloc(nmemb, size);
	i = 0;
	while (i < 40)
	{
		c = ptr[i];
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
	write(1, "new4", 4);

	free(ptr);
	i = 0;
	while (i < 40)
	{
		c = ptr[i];
		write(1, &c, 1);
		i++;
	}
}*/