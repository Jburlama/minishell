/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:22:39 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/10 21:03:23 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_exec	*t_exec_fill(t_exec **exec, t_token *token)
{
	char	*str;

	if (!(*exec)->args)
		str = ft_strdup(token->content);
	else
	{
		str = ft_strjoin((*exec)->args, token->content);
		free((*exec)->args);
	}
	(*exec)->args = str;
	if ((*exec)->args == NULL)
		return (NULL);
	return (*exec);
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
