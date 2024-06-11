/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:20:43 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/10 21:03:41 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*parse_exec(t_token **tokens)
{
	t_exec	*exec;
	void	*root;

	exec = ft_calloc(sizeof(*exec), 1);
	if (exec == NULL)
		return (NULL);
	exec->type = EXEC;
	root = exec;
	while ((*tokens) && *(*tokens)->content != '|')
	{
		root = parse_redir(root, tokens);
		if (!(*tokens))
			break ;
		if (t_exec_fill(&exec, *tokens) == NULL)
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
	if (*tokens && *(*tokens)->content == '|')
	{
		(*tokens) = (*tokens)->next;
		root = construct_pipe(root, parse_pipe(tokens));
	}
	return (root);
}
