/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/20 18:12:19 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_tree(t_data *data)
{
	t_token	*tokens_ptr;

	if (data->head)
	{
		tokens_ptr = data->head;
		data->root = parse_and(&tokens_ptr, data);
		if (data->root == NULL)
			panic("error parsing tree\n", data);
	}
	else
		data->root = NULL;
	clear_list(data);
	data->tail = NULL;
}
