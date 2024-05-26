/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:51:10 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/26 18:56:50 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	get_line()
{
	int	i;
	char *line;

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
	i = -1;
	while (rl_line_buffer[++i])
	{
		if (!is_white_space(rl_line_buffer[i]))
			break ;
	}
	if (!rl_line_buffer[i])
		return ;
	add_history(rl_line_buffer);
}

bool is_white_space(char c)
{
	if (c <= 13 || c == 32)
		return (true);
	return (false);
}
