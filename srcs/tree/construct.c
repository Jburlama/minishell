/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:22:39 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 18:40:37 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*construct_exec(void)
{
	t_exec	*node;

	node = ft_calloc(sizeof(*node), 1);
	if (node == NULL)
		return (NULL);
	node->args = ft_calloc(sizeof(node->args), 1);
	if (node->args == NULL)
		return (NULL);
	node->type = EXEC;
	return (node);
}

char	**add_to_args(char **args, char *content)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = ft_calloc(sizeof(new_args), i + 2);
	if (new_args == NULL)
		return (clear_args(args), clear_args(new_args), NULL);
	i = 0;
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (new_args[i] == NULL)
			return (clear_args(args), clear_args(new_args), NULL);
		i++;
	}
	new_args[i] = ft_strdup(content);
	if (new_args[i] == NULL)
		return (clear_args(args), clear_args(new_args), NULL);
	clear_args(args);
	return (new_args);
}

void	*construct_redir(void	*root, t_token **tokens)
{
	t_redir	*ptr;
	t_redir	*new;

	new = ft_calloc(sizeof(*new), 1);
	if (new == NULL)
		return (NULL);
	new->type = REDIR;
	new->file_type = (*tokens)->type;
	new->file = ft_strdup((*tokens)->content);
	if (new->file == NULL)
		return (NULL);
	if (((t_exec *)root)->type == EXEC)
	{
		new->down = root;
		(*tokens) = (*tokens)->next;
		return (new);
	}
	ptr = root;
	while (((t_exec *)ptr->down)->type != EXEC)
		ptr = ptr->down;
	new->down = ptr->down;
	ptr->down = new;
	(*tokens) = (*tokens)->next;
	return (root);
}

void	*construct_pipe(void *l, void *r)
{
	t_pipe	*pipe;

	pipe = ft_calloc(sizeof(*pipe), 1);
	if (pipe == NULL)
		return (NULL);
	pipe->type = PIPE;
	pipe->left = l;
	pipe->right = r;
	return (pipe);
}
