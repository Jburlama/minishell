/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:54:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 17:42:53 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data)
{
	if (data->root)
		rumcmd(data->root, data);
	exit(errno);
}

void	rumcmd(void *root, t_data *data)
{
	if (((t_exec *)root)->type == EXEC)
		rumexec(root, data);
	else if (((t_exec *)root)->type == REDIR)
		rumredir(root, data);
}
