/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:49:21 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/10 17:05:05 by vbritto-         ###   ########.fr       */
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
		cmd_pwd(data);
	else if (node->builtin == EXPORT)
		cmd_export(data, node);
	else if (node->builtin == UNSET)
		cmd_unset(data, node);
	else if (node->builtin == ENV)
		cmd_env(data);
}

int	check_root(void *root)
{
	if (((t_cond *)root)->type == AND && ((t_cond *)root)->is_block == true)
		return (1);
	else if ((((t_exec *)root)->builtin != NO_B))
		return (2);
	else if (((t_cond *)root)->type == OR)
		return (3);
	return (0);
}
void	check_pipe(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (((t_pipe *)root)->is_block == true)
	{
		pid = save_fork(data);
		wstatus = 0;
		if (pid == 0)
		{
			default_sig();
			if (root)
				runcmd(root, data);
			exit(errno);
		}
		waitpid(pid, &wstatus, 0);
	}
}

void	check_and(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (check_root(((t_cond *)root)->left) == 1)
	{
		pid = save_fork(data);
		if (pid == 0)
			execute(((t_cond *)root)->left, data);
		waitpid(pid, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == 0)
			find_root(((t_cond *)root)->right, data);
	}
	else if (check_root(((t_cond *)root)->left) == 2)
	{
		execute_builtins(((t_cond *)root)->left, data);
		if (data->builtin_fail == false)
			find_root(((t_cond *)root)->right, data);
	}
	else
		execute(root, data);
}

void	check_or(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (check_root(((t_cond *)root)->left) == 3)
	{
		pid = save_fork(data);
		if (pid == 0)
			execute(((t_cond *)root)->left, data);
		waitpid(pid, &wstatus, 0);
		if (WEXITSTATUS(wstatus) != 0)
			find_root(((t_cond *)root)->right, data);
	}
	else if (check_root(((t_cond *)root)->left) == 2)
	{
		execute_builtins(((t_cond *)root)->left, data);
		if (data->builtin_fail == false)
			find_root(((t_cond *)root)->right, data);
	}
	else
	{
		execute(((t_cond *)root)->left, data);
		if (check_root(((t_cond *)root)->right) == 2)
			execute_builtins(((t_cond *)root)->left, data);
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

