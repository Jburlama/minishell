/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rumredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:16 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 17:31:45 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rumredir(void *root, t_data *data)
{
	int		out;

	if (((t_redir *)root)->file_type == O)
	{
		out = open(((t_redir *)root)->file, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		dup2(out, STDOUT_FILENO);
	}
	rumcmd(((t_redir *)root)->down, data);
}
