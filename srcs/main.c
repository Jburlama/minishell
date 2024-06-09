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
		create_tree(&data);
		print_tree(data.root);
		clear_list(&data.head);
	}
	free(rl_line_buffer);
}

void	print_tree(void	*root)
{
	t_exec	*exec;
	t_redir	*redir;

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
