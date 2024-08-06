/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:41:35 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/06 10:19:10 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] == 'n')
			i++;
	}
	if (arg[i] == '\0')
		return (true);
	else
		return (false);
}

void	cmd_echo(t_exec *node)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (node->args[i] && node->args[i][0] == '-' && node->args[i][1] == 'n')
	{
		n = check_n(node->args[i]);
		while (node->args[i] != NULL)
		{
			if (!check_n(node->args[i]))
				break ;
			i++;
		}
	}
	while (node->args[i])
	{
		if (node->args[i][0] != '\0')
			ft_printf("%s", node->args[i]);
		if (node->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (n == false)
		write(1, "\n", 1);
}
