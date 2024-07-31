/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:05:14 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/10 18:12:27 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	runpipe(t_pipe *root, t_data *data)
{
	int	fds[2];
	int	wstatus;
	int	exit_code;

	pipe(fds);
	if (save_fork(data) == 0)
	{
		default_sig();
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		runcmd(root->left, data);
	}
	if (save_fork(data) == 0)
	{
		default_sig();
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		runcmd(root->right, data);
	}
	close(fds[1]);
	close(fds[0]);
	exit_code = runpipe_wait(&wstatus, data);
	exit(exit_code);
}

int	runpipe_wait(int *wstatus, t_data *data)
{
	int	exit_code;

	clear_args(data->env);
	clear_args(data->export);
	clear_tree(data->root);
	while (waitpid(-1, wstatus, 0) > 0)
	{
		if (WIFEXITED(*wstatus))
			exit_code = WEXITSTATUS(*wstatus);
	}
	return (exit_code);
}
