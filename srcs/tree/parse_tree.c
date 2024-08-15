/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:20:43 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/20 18:16:17 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*parse_exec(t_token **tokens, t_data *data)
{
	t_exec	*exec;
	void	*root;

	if ((*tokens) && (*tokens)->type == SPECIAL && *(*tokens)->content == '(')
		return (parse_block(tokens, data));
	exec = construct_exec();
	if (exec == NULL)
		return (NULL);
	root = exec;
	while ((*tokens) && *(*tokens)->content != '|' && *(*tokens)->content != '&'
		&& *(*tokens)->content != ')')
	{
		root = parse_redir(root, tokens, data);
		if (root == NULL || leave_loop(tokens) == 1)
			break ;
		exec->args = add_to_args(exec->args, (*tokens)->content);
		if (ft_memcmp((*tokens)->content, exec->args[0],
				ft_strlen(exec->args[0]) + 1) == 0)
			exec->builtin = (*tokens)->builtin;
		if (exec->args == NULL)
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	return (root);
}

int	leave_loop(t_token **tokens)
{
	if (!(*tokens))
		return (1);
	if (*(*tokens)->content == '|'
		|| *(*tokens)->content == '&' || *(*tokens)->content == ')')
	{
		if ((*tokens)->type != SPECIAL)
			return (0);
		if (*(*tokens)->content == '|' || *(*tokens)->content == '&')
		{
			if (ft_strlen((*tokens)->content) == 1)
				return (1);
			if (ft_strlen((*tokens)->content) == 2
				&& ((*((*tokens)->content + 1) == '|')
					|| (*((*tokens)->content + 1) == '&')))
				return (1);
		}
		if (*(*tokens)->content == ')')
			return (1);
	}
	return (0);
}

void	*parse_redir(void *root, t_token **tokens, t_data *data)
{
	void	*ret;

	ret = root;
	while ((*tokens) && (*tokens)->type == WHITE_SPACE)
		(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type == SPECIAL
		&& (*(*tokens)->content == '<' || *(*tokens)->content == '>'))
	{
		(*tokens) = (*tokens)->next;
		if (*tokens)
		{
			ret = construct_redir(ret, tokens, data);
			(*tokens) = (*tokens)->next;
		}
		if (ret == NULL)
			return (NULL);
		while ((*tokens) && (*tokens)->type == WHITE_SPACE)
			(*tokens) = (*tokens)->next;
	}
	while ((*tokens) && (*tokens)->type == WHITE_SPACE)
		(*tokens) = (*tokens)->next;
	return (ret);
}

void	*parse_block(t_token **tokens, t_data *data)
{
	void	*root;

	(*tokens) = (*tokens)->next;
	root = parse_and(tokens, data);
	if (root == NULL)
		return (NULL);
	if (*tokens)
		(*tokens) = (*tokens)->next;
	if (*tokens)
	{
		while ((*tokens) && (*tokens)->type == WHITE_SPACE)
			(*tokens) = (*tokens)->next;
		root = parse_redir(root, tokens, data);
	}
	((t_exec *)root)->is_block = true;
	return (root);
}

void	*parse_pipe(t_token **tokens, t_data *data)
{
	void	*root;

	root = parse_exec(tokens, data);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content == '|'
		&& ft_strlen((*tokens)->content) == 1)
	{
		(*tokens) = (*tokens)->next;
		root = construct_pipe(root, parse_pipe(tokens, data));
		if (root == NULL)
			return (NULL);
	}
	return (root);
}
