/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_root_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:17:31 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/06 12:47:27 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_and_aux(void *root, t_data *data)
{
	find_root(((t_cond *)root)->left, data);
	if (check_root(((t_cond *)root)->right) == 2)
		execute_builtins(((t_cond *)root)->right, data);
	else
		find_root(((t_cond *)root)->right, data);
}
