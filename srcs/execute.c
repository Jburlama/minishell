/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:54:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 18:38:49 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}
