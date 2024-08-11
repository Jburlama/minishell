/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:42:11 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/06 10:19:18 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(void *root);

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
			// for (t_token *ptr = data.head; ptr; ptr = ptr->next)
			// 	printf("%s\n", ptr->content);
			if (data.exit_code != 2 && data.exit_code != 1)
			{
				create_tree(&data);
				// print_tree(data.root);
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

void	print_tree(void *root)
{
	if (((t_exec *)root)->type == EXEC)
	{
		printf("node exec\n");
		for (int i = 0; ((t_exec *)root)->args[i]; i++)
			printf("%s / ", ((t_exec *)root)->args[i]);
		printf("\n");
		return ;
	}
	else if (((t_cond *)root)->type == AND)
	{
		printf("node and\n");
		print_tree(((t_cond *)root)->left);
		print_tree(((t_cond *)root)->right);
	}
	else if (((t_cond *)root)->type == OR)
	{
		printf("node or\n");
		print_tree(((t_cond *)root)->left);
		print_tree(((t_cond *)root)->right);
	}
	else if (((t_cond *)root)->type == PIPE)
	{
		printf("node pipe\n");
		print_tree(((t_cond *)root)->left);
		print_tree(((t_cond *)root)->right);
	}
}
