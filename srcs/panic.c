/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:08:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 20:56:00 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	panic(char *msg, t_data *data)
{
	if (data->head)
		clear_list(data);
	if (data->root)
		clear_tree(&data->root);
	perror(msg);
	exit(errno);
}
