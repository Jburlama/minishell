/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:54:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 20:24:53 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data)
{
	rumcmd(data->root);
}

void	rumcmd(void *root)
{
	if (((t_exec *)root)->type == EXEC)
		rumexec(root);
}

void	rumexec(t_exec *node)
{
	char	*pathname;
	char	**argv;

	
}
