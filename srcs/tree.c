/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/10 20:22:53 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_tree(t_data *data)
{
	t_token	*tokens_ptr;

	tokens_ptr = data->head;
	data->root = parse_exec(&tokens_ptr);
	if (data->root == NULL)
		panic("error calling parse_exec", data);
}
