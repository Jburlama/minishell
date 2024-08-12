/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:40:34 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/31 19:09:13 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status_exit;

char	*get_line(t_data *data)
{
	char	*line;

	handle_signal();
	dup2(STDERR_FILENO, STDIN_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline("Minishell: ");
	if (g_status_exit == 2)
	{
		data->exit_code = 130;
		data->print_exit_code = data->exit_code;
		data->exit_code = 0;
	}
	if (!line)
	{
		free(rl_line_buffer);
		clear_args(data->env);
		clear_args(data->export);
		printf("exit\n");
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
