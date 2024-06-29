/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:27:25 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/28 15:46:08 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_and_builtin(t_data *data)
{
    void  *root;

    root = data->root;
    if (((t_pipe *)root)->type == PIPE)
        return ;
    else
        execute_builtins(data->root, data);
}