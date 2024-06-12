/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:32:03 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 22:14:01 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(void	*root);

char	**ev;

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	// ev = env;
	(void)argc;
	(void)argv;
	(void)env;
	handle_signal();
	ft_memset(&data, 0, sizeof(data));
	while (42)
	{
		get_line();
		tokenize(&data);
		for (t_token *ptr = data.head; ptr; ptr = ptr->next)
			printf("content: %s | type %i\n", ptr->content, ptr->type);
		clear_list(&data.head);
		continue ;
		create_tree(&data);
		// if (save_fork(&data) == 0)
		// 	execute(&data);
		// wait(NULL);
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
