/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:00:35 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/10 18:10:38 by Jburlama         ###   ########.fr       */
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
	ft_memset(&data, 0, sizeof(data));
	data.env = env;
	while (42)
	{
		get_line();
		// if(check(rl_line_buffer) == 2) 
		// 	continue;
		tokenize(&data);
		// prepare_token(&data);
		// for (t_token *ptr = data.head; ptr; ptr = ptr->next)
		// 	printf("content: %s | type %i | file %i\n",
		//   		ptr->content, ptr->type, ptr->file);
		// clear_list(&data);
		// continue ;
		create_tree(&data);
		// print_tree(data.root);
		execute(&data);
		clear_tree(data.root);
	}
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
		printf("type: %i\n", pipe->type);
		print_tree(pipe->left);
		print_tree(pipe->right);
	}
	else if (((t_cond *)root)->type == OR || ((t_cond *)root)->type == AND)
	{
		cont = root;
		printf("type: %i\n", cont->type);
		print_tree(cont->left);
		print_tree(cont->right);
	}
}
