/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:42:11 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/15 18:32:27 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status_exit = 0;

void	update_exit_code(t_data	*data)
{
	data->print_exit_code = data->exit_code;
	data->exit_code = 0;
	g_status_exit = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	start_data(&data, env);
	while (42)
	{
		get_line(&data);
		if (check(rl_line_buffer, &data) != 2)
		{
			tokenize(&data);
			prepare_token(&data);
			if (data.exit_code != 2 && data.exit_code != 1)
			{
				create_tree(&data);
				find_root(data.root, &data);
				clear_tree(data.root);
			}
		}
		update_exit_code(&data);
	}
	clear_args(data.env);
	clear_args(data.export);
	free(rl_line_buffer);
}
