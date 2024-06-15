/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:54:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 18:41:41 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_data *data)
{
	if (data->root)
		runcmd(data->root, data);
	exit(errno);
}

void	runcmd(void *root, t_data *data)
{
	if (((t_exec *)root)->type == EXEC)
		runexec(root, data);
	else if (((t_exec *)root)->type == REDIR)
		runredir(root, data);
	else if (((t_pipe *)root)->type == PIPE)
		runpipe(root, data);
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

void	runpipe(t_pipe *root, t_data *data)
{
	int	fds[2];

	pipe(fds);
	if (save_fork(data) == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		runcmd(root->left, data);
	}
	if (save_fork(data) == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		runcmd(root->right, data);
	}
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	wait(NULL);
	clear_tree(data->root);
	exit(errno);
}
