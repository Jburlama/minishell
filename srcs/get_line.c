/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:51:10 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/26 18:59:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_line(void)
{
	char	*line;

	line = readline(GREEN "Minishell: " RESET);
	if (!line)
	{
		free(rl_line_buffer);
		exit(0);
	}
	free(line);
	if (ft_memcmp(rl_line_buffer, "exit\0", 5) == 0)
	{
		free(rl_line_buffer);
		exit(0);
	}
	add_history(rl_line_buffer);
}
