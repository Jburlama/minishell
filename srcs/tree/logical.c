/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:44:23 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/18 20:44:42 by Jburlama         ###   ########.fr       */
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
	waitpid(pid, &wstatus, 0);
	if (WEXITSTATUS(wstatus) == 0)
	{
		clear_tree(data->root);
		exit(0);
	}
	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->right, data);
	waitpid(pid, &wstatus, 0);
	clear_tree(data->root);
	exit(0);
}

void	runand(t_cond *root, t_data *data)
{
	int	pid;
	int	wstatus;

	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->left, data);
	waitpid(pid, &wstatus, 0);
	if (WEXITSTATUS(wstatus) != 0)
	{
		clear_tree(data->root);
		exit(1);
	}
	pid = save_fork(data);
	if (pid == 0)
		runcmd(root->right, data);
	waitpid(pid, &wstatus, 0);
	clear_tree(data->root);
	exit(0);
}

void	*parse_or(t_token **tokens)
{
	void		*root;
	enum e_type	type;

	root = parse_pipe(tokens);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content == '|')
	{
		type = OR;
		(*tokens) = (*tokens)->next;
		root = construct_cond(root, parse_or(tokens), type);
		if (root == NULL)
			return (NULL);
	}
	return (root);
}

void	*parse_and(t_token **tokens)
{
	void		*root;
	enum e_type	type;

	root = parse_or(tokens);
	if (root == NULL)
		return (NULL);
	if (*tokens && *(*tokens)->content != ')')
	{
		type = AND;
		(*tokens) = (*tokens)->next;
		root = construct_cond(root, parse_and(tokens), type);
		if (root == NULL)
			return (NULL);
	}
	return (root);
}
