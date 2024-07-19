/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:42:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/19 10:09:47 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(void *root, t_data *data)
{
	int	pid;
	int	wstatus;

	update_signals();
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
	if (WIFSIGNALED(wstatus))
		if (WCOREDUMP(wstatus))
			write(1, "Quit (core dumped)\n", 19);
}

void	runcmd(void *root, t_data *data)
{
	if (((t_exec *)root)->type == EXEC)
		runexec(root, data);
	else if (((t_redir *)root)->type == REDIR)
		runredir(root, data);
	else if (((t_pipe *)root)->type == PIPE)
		runpipe(root, data);
	else if (((t_cond *)root)->type == OR)
		runor(root, data);
	else if (((t_cond *)root)->type == AND)
		runand(root, data);
}

void	runredir(t_redir *root, t_data *data)
{
	int		fd;

	if (root->file_type == O)
	{
		fd = open(root->file, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (root->file_type == APEND)
	{
		fd = open(root->file, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (root->file_type == I)
		read_input(root, data);
	runcmd(((t_redir *)root)->down, data);
}

void	read_input(t_redir *root, t_data *data)
{
	int	fd;

	if (access(root->file, F_OK) == 0)
	{
		fd = open(root->file, O_RDWR);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		perror(root->file);
		clear_tree(data->root);
		exit(errno);
	}
}

//// VIDE EXECUTE