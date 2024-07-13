/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:53:03 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/13 16:54:42 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	status_exit;

void	print_tree(void	*root);

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	start_data(&data, env);
	while (42)
	{
		handle_signal();
		get_line(&data);
		if(check(rl_line_buffer, &data) == 2)
		{	
			status_exit = 0;
			continue;
		}
		tokenize(&data);
		prepare_token(&data);
		/*for (t_token *ptr = data.head; ptr; ptr = ptr->next)
			printf("content: %s | type %i\n", ptr->content, ptr->type);
		clear_list(&data.head);
		continue ;*/
		create_tree(&data);
		//print_tree(data.root);
		//continue ;
		//execute(data.root, &data);
		//print_tree(data.root);
		find_root(data.root, &data);
		clear_tree(data.root);
		/*if (find_root(data.root, &data) == 0)
		{
			if (save_fork(&data) == 0)
				execute(&data);
			wait(NULL);
		}*/
		// print_tree(data.root);
		clear_tree(data.root);
	}
	clear_args(data.env);
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
