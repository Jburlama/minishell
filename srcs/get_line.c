/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:51:10 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/05 18:29:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_line(void)
{
	char	*line;

	handle_signal();
	line = readline(GREEN "Minishell: " RESET);
	if (!line)
	{
		free(rl_line_buffer);
		printf("exit\n");
		exit(0);
	}
	if (ft_memcmp(rl_line_buffer, "exit\0", 5) == 0)
	{
		free(rl_line_buffer);
		exit(0);
	}
	add_history(rl_line_buffer);
	return (line);
}

bool	is_white_space(char c)
{
	if (c <= 13 || c == 32)
		return (true);
	else
		return (false);
}
