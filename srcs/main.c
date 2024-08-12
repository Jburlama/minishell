/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:42:11 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/12 13:00:15 by vbritto-         ###   ########.fr       */
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
/*
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
			for (t_token *ptr = data.head; ptr; ptr = ptr->next)
				printf("content: %s | type %i\n", ptr->content, ptr->type);
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
}*/

void	print_tree(void	*root);

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
			for (t_token *ptr = data.head; ptr; ptr = ptr->next)
				printf("content: %s | type %i\n", ptr->content, ptr->type);
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

void	print_tree(void	*root)
{
	t_exec	*exec;
	t_redir	*redir;
	t_pipe	*pipe;
	t_cond	*cont;

	if (!root)
		return ;
	else if (((t_exec *)root)->type == EXEC)
	{
		exec = root;
		printf("is block: %i | ", exec->is_block);
		printf("type: %i | args: ", exec->type);
		int i = 0;
		while (exec->args[i])
		{
			printf("%s; ", exec->args[i]);
			i++;
		}
		printf("\n");
		return ;
	}
	else if (((t_redir *)root)->type == REDIR)
	{
		redir = root;
		printf("type: %i | file_type: %i | quote_type: %i | file: %s\n",
		 redir->type, redir->file_type, redir->quote_type, redir->file);
		print_tree(redir->down);
	}
	else if (((t_redir *)root)->type == PIPE)
	{
		pipe = root;
		printf("is block: %i | ", pipe->is_block);
		printf("type: %i\n", pipe->type);
		printf("\n");
		printf("LEFT\n");
		print_tree(pipe->left);
		printf("\n");
		printf("RIGHT\n");
		print_tree(pipe->right);
	}
	else if (((t_cond *)root)->type == OR || ((t_cond *)root)->type == AND)
	{
		cont = root;
		printf("is block: %i | ", cont->is_block);
		printf("type: %i\n", cont->type);
		printf("\n");
		printf("LEFT\n");
		print_tree(cont->left);
		printf("\n");
		printf("RIGHT\n");
		print_tree(cont->right);
	}
}