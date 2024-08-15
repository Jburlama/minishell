/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:49:21 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/15 21:19:44 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_builtins(t_exec *node, t_data *data)
{
	if (node->builtin == ECHO)
		cmd_echo(node);
	else if (node->builtin == CD)
		cmd_cd(data, node);
	else if (node->builtin == PWD)
		cmd_pwd(data, node);
	else if (node->builtin == EXPORT)
		cmd_export(data, node);
	else if (node->builtin == UNSET)
		cmd_unset(data, node);
	else if (node->builtin == EXIT)
		cmd_exit(data, node);
}

int	check_root(void *root)
{
	if ((((t_cond *)root)->type == AND || ((t_cond *)root)->type == OR)
		&& ((t_cond *)root)->is_block == true)
		return (1);
	else if ((((t_exec *)root)->builtin != NO_B)
		&& ((t_cond *)root)->type == OR)
		return (4);
	else if ((((t_exec *)root)->builtin != NO_B))
		return (2);
	return (0);
}

void	check_and(void *root, t_data *data)
{
	if (check_root(((t_cond *)root)->left) == 1)
	{
		find_root(((t_cond *)root)->left, data);
		if (data->exit_code == 0)
		{
			if (check_root(((t_cond *)root)->right) == 2)
				execute_builtins(((t_cond *)root)->right, data);
			else
				find_root(((t_cond *)root)->right, data);
		}
	}
	else if ((check_root(((t_cond *)root)->left) == 2))
	{
		execute_builtins(((t_cond *)root)->left, data);
		if (data->exit_code == 0)
			find_root(((t_cond *)root)->right, data);
	}
	else
	{
		find_root(((t_cond *)root)->left, data);
		if (data->exit_code == 0)
			find_root(((t_cond *)root)->right, data);
	}
}

void	check_or(void *root, t_data *data)
{
	if (check_root(((t_cond *)root)->left) == 1)
	{
		find_root(((t_cond *)root)->left, data);
		if (data->exit_code != 0)
		{
			if (check_root(((t_cond *)root)->right) == 2)
				execute_builtins(((t_cond *)root)->right, data);
			else
				find_root(((t_cond *)root)->right, data);
		}
	}
	else if ((check_root(((t_cond *)root)->left) == 2))
	{
		execute_builtins(((t_cond *)root)->left, data);
		if (data->exit_code != 0)
			find_root(((t_cond *)root)->right, data);
	}
	else
	{
		find_root(((t_cond *)root)->left, data);
		if (data->exit_code != 0)
			find_root(((t_cond *)root)->right, data);
	}
}

void	find_root(void *root, t_data *data)
{
	t_redir	*find_cd;

	if (root != NULL)
	{
		if (((t_pipe *)root)->type == PIPE)
			execute(root, data);
		else if (((t_cond *)root)->type == AND)
			check_and(((t_cond *)root), data);
		else if (((t_cond *)root)->type == OR)
			check_or(((t_cond *)root), data);
		else if (((t_redir *)root)->type == REDIR)
		{
			find_cd = root;
			while (find_cd->type != EXEC)
				find_cd = find_cd->down;
			if (((t_exec *)find_cd)->builtin == CD)
				runredir(root, data);
			else
				execute(root, data);
		}
		else if (((t_exec *)root)->builtin != NO_B)
			execute_builtins(((t_exec *)root), data);
		else if (((t_exec *)root)->type == EXEC)
			execute(root, data);
	}
}
