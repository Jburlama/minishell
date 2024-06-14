/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:20:43 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 17:19:07 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*parse_exec(t_token **tokens)
{
	int		i;
	t_exec	*exec;
	void	*root;

	exec = construct_exec();
	if (exec == NULL)
		return (NULL);
	root = exec;
	i = 0;
	while ((*tokens) && *(*tokens)->content != '|')
	{
		root = parse_redir(root, tokens);
		if (!(*tokens) || root == NULL)
			break ;
		if ((*tokens)->type == WHITE_SPACE)
		{
			(*tokens) = (*tokens)->next;
			continue ;
		}
		exec->args = add_to_args(exec->args, (*tokens)->content);
		if (exec->args == NULL)
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	return (root);
}

void	*parse_redir(void *root, t_token **tokens)
{
	void	*ret;

	ret = root;
	while ((*tokens) && ((*tokens)->type == SPECIAL))
	{
		(*tokens) = (*tokens)->next;
		if (*tokens)
			ret = construct_redir(ret, tokens);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

void	*parse_pipe(t_token **tokens)
{
	void	*root;

	root = parse_exec(tokens);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content == '|')
	{
		(*tokens) = (*tokens)->next;
		root = construct_pipe(root, parse_pipe(tokens));
		if (root == NULL)
			return (NULL);
	}
	return (root);
}
