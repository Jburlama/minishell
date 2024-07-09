/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:49:21 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/09 16:04:37 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_builtins(t_exec *node, t_data *data)
{
	if (node->builtin == ECHO)
		cmd_echo(node);
	if (node->builtin == CD)
		cmd_cd(data, node);
	if (node->builtin == PWD)
		cmd_pwd();
	if (node->builtin == EXPORT)
		cmd_export(data, node);
	if (node->builtin == UNSET)
		cmd_unset(data, node);
	if (node->builtin == ENV)
		cmd_env(data);
}

int	check_root(void *root)
{
	if ((((t_cond *)root)->type == AND) || ((t_cond *)root)->type == OR)
		return (1);
	/*if (((t_exec *)root)->builtin != NO_B)
		return (2);*/
	return (0);
}

void	check_and(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (check_root(((t_cond *)root)->left) == 1)
	{
		pid = save_fork(data);
		if (pid == 0)
			runcmd(((t_cond *)root)->left, data);
		waitpid(pid, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == 0)
		{
			if (check_root(((t_cond *)root)->right) == 1)
			{
				pid = save_fork(data);
				if (pid == 0)
					runcmd(((t_cond *)root)->right, data);
				waitpid(pid, &wstatus, 0);
			}
		}
	}
	else
	{
		find_root(((t_cond *)root)->left, data);
		find_root(((t_cond *)root)->right, data);
	}
}

void	check_or(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (check_root(((t_cond *)root)->left) == 1)
	{
		pid = save_fork(data);
		if (pid == 0)
			runcmd(((t_cond *)root)->left, data);
		waitpid(pid, &wstatus, 0);
		if (WEXITSTATUS(wstatus) != 0)
		{
			if (check_root(((t_cond *)root)->right) == 1)
			{
				pid = save_fork(data);
				if (pid == 0)
					runcmd(((t_cond *)root)->right, data);
				waitpid(pid, &wstatus, 0);
			}
		}
	}
	else
	{
		find_root(((t_cond *)root)->left, data);
		find_root(((t_cond *)root)->right, data);
	}
}

void	find_root(void *root, t_data *data)
{
	
	if (root != NULL)
	{
		if (((t_pipe *)root)->type == PIPE)
			execute(root, data);
		else if (((t_cond *)root)->type == AND)
			check_and(((t_cond *)root), data);
		else if (((t_cond *)root)->type == OR)
			check_or(((t_cond *)root), data);
		else if (((t_exec *)root)->type == REDIR)
			execute(root, data);
		else if (((t_exec *)root)->builtin != NO_B)
			execute_builtins(((t_exec *)root), data);
		else if (((t_exec *)root)->type == EXEC)
			execute(root, data);
	}
}

/*
int	pipe_and_builtin(t_data *data)
{
	void	*root;

	root = data->root;
	if (root != NULL)
	{
		if (((t_pipe *)root)->type == PIPE)
			return (0);
		if (((t_exec *)root)->builtin != NO_B)
		{
			execute_builtins(data->root, data);
			return (1);
		}
	}
	return (0);*/
