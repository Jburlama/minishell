/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:08:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/31 16:09:05 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	panic(char *msg, t_data *data)
{
	clear_list(&data->head);
	perror(msg);
	exit(errno);
}
