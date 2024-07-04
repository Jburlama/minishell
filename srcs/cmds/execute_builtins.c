/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:49:21 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/04 17:43:18 by vbritto-         ###   ########.fr       */
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

int	find_root(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	if (root != NULL)
	{
		if (((t_pipe *)root)->type == PIPE)
			return (0);
		else if (((t_cond *)root)->type == AND)
		{
			if (find_root(((t_cond *)root)->left, data) == 0)
			{
				pid = save_fork(data);
				if (pid == 0)
					runcmd(((t_cond *)root)->left, data);
				waitpid(pid, &wstatus, 0);
				if (WEXITSTATUS(wstatus) == 0)
				{
					pid = save_fork(data);
					if (pid == 0)
						runcmd(((t_cond *)root)->right, data);
					waitpid(pid, &wstatus, 0);
				}
				exit (1);
			}
			//return (1);
			
		}/*
		else if (((t_cond *)root)->type == OR)
		{

		}*/
		else if (((t_exec *)root)->builtin != NO_B)
		{
			execute_builtins(data->root, data);
			return (1);
		}
	}
	return (0);
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
