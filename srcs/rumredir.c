/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rumredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:16 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 17:57:39 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rumredir(void *root, t_data *data)
{
	int		fd;

	if (((t_redir *)root)->file_type == O)
	{
		fd = open(((t_redir *)root)->file, O_CREAT | O_TRUNC | O_RDWR,
			 S_IRWXU);
		dup2(fd, STDOUT_FILENO);
	}
	else if (((t_redir *)root)->file_type == APEND)
	{
		fd = open(((t_redir *)root)->file, O_CREAT | O_APPEND | O_RDWR,
			 S_IRWXU);
		dup2(fd, STDOUT_FILENO);
	}
	else if (((t_redir *)root)->file_type == I)
	{
		fd = open(((t_redir *)root)->file, O_CREAT | O_RDWR, S_IRWXU);
		dup2(fd, STDIN_FILENO);
	}
	rumcmd(((t_redir *)root)->down, data);
}
