/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:32:03 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/09 21:50:40 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tree(void	*root);

int	main(void)
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
		clear_list(&data.head);
		print_tree(data.root);
		clear_tree(data.root);
	}
	free(rl_line_buffer);
}

void	print_tree(void	*root)
{
	t_exec	*exec;
	t_redir	*redir;

	if (!root)
		return ;
	if (((t_exec *)root)->type == EXEC)
	{
		exec = root;
		printf("type: %i | args: %s\n", exec->type, exec->args);
		return ;
	}
	redir = root;
	printf("type: %i | file_type: %i | file: %s\n", redir->type, redir->file_type, redir->file);
	print_tree(redir->down);
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
}
