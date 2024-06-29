/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:09:39 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/28 18:01:59 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**export(char **old_env, char *arg, int i)
{
	char	**new_env;

	new_env = NULL;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i] != NULL)
	{
		new_env[i] = ft_calloc(ft_strlen(old_env[i]) + 1, sizeof(char));
		if (!new_env[i])
			return (NULL);
		ft_strlcpy(new_env[i], old_env[i], ft_strlen(old_env[i]) + 1);
		i++;
	}
	new_env[i] = ft_calloc(ft_strlen(arg) + 1, sizeof(char *));
	if (!new_env[i])
		return (NULL);
	ft_strlcpy(new_env[i], arg, ft_strlen(arg) + 1);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	cmd_export(t_data *data, t_exec *node)
{
	int		i;

	i = 0;
	if (ft_isdigit(node->args[1][0]))
		return ;
	while (node->args[1][i])
	{
		if (node->args[1][i] == '=')
			break;
		i++;
	}
	if (node->args[1][i] == '=')
	{
		i = 0;
		while (data->env[i])
			i++;
		data->env = export(data->env, node->args[1], i);
	}
	return ;
}
