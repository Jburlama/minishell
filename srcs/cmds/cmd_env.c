/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:19:30 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/02 20:11:09 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check leaks
void	cmd_env(t_data *data, t_exec *node)
{
	int	i;

	i = 0;
	if (node->args[1] == NULL)
	{
		while (data->env[i] != NULL)
		{
			ft_printf("%s\n", data->env[i]);
			i++;
		}
	}
	else
	{
		ft_printf("%s: %s: %s\n", node->args[0], node->args[1],
			"No such file or directory");
		data->builtin_fail = true;
	}
}
