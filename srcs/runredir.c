/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:16 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 18:24:05 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runredir(t_redir *root, t_data *data)
{
	int		fd;

	if (root->file_type == O)
	{
		fd = open(root->file, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		dup2(fd, STDOUT_FILENO);
	}
	else if (root->file_type == APEND)
	{
		fd = open(root->file, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
		dup2(fd, STDOUT_FILENO);
	}
	else if (root->file_type == I)
	{
		fd = open(root->file, O_CREAT | O_RDWR, S_IRWXU);
		dup2(fd, STDIN_FILENO);
	}
	runcmd(((t_redir *)root)->down, data);
}
