/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rng.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:31:31 by Jburlama          #+#    #+#             */
/*   Updated: 2024/04/01 17:07:02 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* return a possitive random integers
* returns -1 if fails
*/
int	ft_rng(void)
{
	int	fd;
	int	rng;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read(fd, &rng, 4) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (rng < 0)
		rng *= -1;
	return (rng);
}
