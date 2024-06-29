/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:51:10 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/29 15:58:43 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_line(t_data *data)
{
	char	*line;

	line = readline(GREEN "Minishell: " RESET);
	if (!line)
	{
		free(rl_line_buffer);
		clear_args(data->env);
		printf("exit\n");
		exit(0);
	}
	if (ft_memcmp(rl_line_buffer, "exit\0", 5) == 0)
	{
		free(rl_line_buffer);
		clear_args(data->env);
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
