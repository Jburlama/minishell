/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 16:31:23 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_tree(t_data *data)
{
	t_token	*tokens_ptr;

	if (data->head)
	{
		tokens_ptr = data->head;
		data->root = parse_cond(&tokens_ptr);
		if (data->root == NULL)
			panic("error parsinf tree\n", data);
	}
	else
		data->root = NULL;
	clear_list(&data->head);
}

void	*parse_cond(t_token **tokens)
{
	void		*root;
	enum e_type	type;

	root = parse_pipe(tokens);
	if (root == NULL)
		return (NULL);
	if (*tokens)
	{
		if (*(*tokens)->content == '|')
			type = OR;
		else
			type = AND;
		(*tokens) = (*tokens)->next;
		root = construct_cond(root, parse_cond(tokens), type);
		if (root == NULL)
			return (NULL);
	}
	return (root);
}
