/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/20 18:17:24 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	runor(t_cond *root, t_data *data)
{
	int	pid;
	int	wstatus;

	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->left, data);
	while (waitpid(-1, &wstatus, 0) > 0)
		;
	if (WEXITSTATUS(wstatus) == 0)
	{
		clear_args(data->env);
		clear_args(data->export);
		clear_tree(data->root);
		exit(0);
	}
	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->right, data);
	clear_args(data->env);
	clear_args(data->export);
	clear_tree(data->root);
	while (waitpid(-1, &wstatus, 0) > 0)
		;
	exit(0);
}

void	runand(t_cond *root, t_data *data)
{
	int	pid;
	int	wstatus;

	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->left, data);
	while (waitpid(-1, &wstatus, 0) > 0)
		;
	if (WEXITSTATUS(wstatus) != 0)
	{
		clear_args(data->env);
		clear_args(data->export);
		clear_tree(data->root);
		exit(1);
	}
	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->right, data);
	clear_args(data->env);
	clear_args(data->export);
	clear_tree(data->root);
	while (waitpid(-1, &wstatus, 0) > 0)
		;
	exit(0);
}

void	*parse_or(t_token **tokens, t_data *data)
{
	void		*root;
	enum e_type	type;

	root = parse_pipe(tokens, data);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content == '|')
	{
		type = OR;
		(*tokens) = (*tokens)->next;
		root = construct_cond(root, parse_or(tokens, data), type);
		if (root == NULL)
			return (NULL);
	}
	return (root);
}

void	*parse_and(t_token **tokens, t_data *data)
{
	void		*root;
	enum e_type	type;

	root = parse_or(tokens, data);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content != ')')
	{
		type = AND;
		(*tokens) = (*tokens)->next;
		root = construct_cond(root, parse_and(tokens, data), type);
		if (root == NULL)
			return (NULL);
	}
	return (root);
}
