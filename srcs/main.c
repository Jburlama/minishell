/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:54:56 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/11 15:55:01 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(void	*root);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	handle_signal();
	ft_memset(&data, 0, sizeof(data));
	while (42)
	{
		get_line();
		tokenize(&data);
		// for (t_token *ptr = data.head; ptr; ptr = ptr->next)
		// 	printf("content: %s | type %i\n", ptr->content, ptr->type);
		// clear_list(&data.head);
		// continue ;
		create_tree(&data);
		print_tree(data.root);
		clear_tree(data.root);
	}
	free(rl_line_buffer);
}

void	print_tree(void	*root)
{
	t_exec	*exec;
	t_redir	*redir;
	t_pipe	*pipe;

	if (!root)
		return ;
	if (((t_exec *)root)->type == EXEC)
	{
		exec = root;
		printf("type: %i | args: %s\n", exec->type, exec->args);
		return ;
	}
	else if (((t_redir *)root)->type == REDIR)
	{
		redir = root;
		printf("type: %i | file_type: %i | file: %s\n", redir->type, redir->file_type, redir->file);
		print_tree(redir->down);
	}
	else if (((t_redir *)root)->type == PIPE)
	{
		pipe = root;
		printf("type: %i\n", pipe->type);
		print_tree(pipe->left);
		print_tree(pipe->right);
	}
}

void	clear_tree(void	*root)
{
	if (((t_exec *)root)->type == EXEC)
	{
		free(((t_exec *)root)->args);
		free(root);
		return ;
	}
	else if (((t_redir *)root)->type == REDIR)
	{
		free(((t_redir *)root)->file);
		clear_tree(((t_redir *)root)->down);
		free(root);
	}
	else if (((t_pipe *)root)->type == PIPE)
	{
		clear_tree(((t_pipe *)root)->left);
		clear_tree(((t_pipe *)root)->right);
		free(root);
	}
}
