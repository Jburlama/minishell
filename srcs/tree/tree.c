/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 16:31:23 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_tree(t_data *data)
{
	t_token	*tokens_ptr;

	if (data->head)
	{
		tokens_ptr = data->head;
		data->root = parse_and(&tokens_ptr);
		if (data->root == NULL)
			panic("error parsing tree\n", data);
	}
	else
		data->root = NULL;
	clear_list(&data->head);
	data->tail = NULL;
}
