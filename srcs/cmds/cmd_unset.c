/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:04 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/28 17:30:16 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**unset(t_data *data, t_exec *node, int i)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = ft_calloc(i, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (data->env[j] != NULL)
	{
		if (ft_memcmp(data->env[j], node->args[1], 
			ft_strlen(node->args[1])) != 0)
		{
			tmp[i] = ft_calloc(ft_strlen(data->env[j]) + 1, sizeof(char));
			if (!tmp[i])
				return (NULL);
			ft_strlcpy(tmp[i], data->env[j], ft_strlen(data->env[j]) + 1);
			j++;
			i++;
		}
		else
			j++;
	}
	tmp[i] = NULL;
	return (clear_args(data->env), tmp);
}

void	cmd_unset(t_data *data, t_exec *node)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
		i++;
	data->env = unset(data, node, i);
}
