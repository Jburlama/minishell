/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:22:39 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 22:11:51 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	*construct_redir(void	*subnode, t_token **tokens)
{
	t_redir	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (ret == NULL)
		return (NULL);
	ret->type = REDIR;
	ret->file_type = (*tokens)->type;
	ret->file = ft_strdup((*tokens)->content);
	if (ret->file == NULL)
		return (NULL);
	ret->down = subnode;
	(*tokens) = (*tokens)->next;
	return (ret);
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
