/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:04 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/06 11:08:31 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**u_env(t_data *data, char *args, int n)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = ft_calloc(n, sizeof(char *));
	if (!tmp)
		return (NULL);
	n = 0;
	while (data->env[j] != NULL)
	{
		if (ft_memcmp(data->env[j], args,
				ft_find_len(data->env[j])) != 0)
		{
			tmp[n] = ft_strdup(data->env[j]);
			j++;
			n++;
		}
		else
			j++;
	}
	clear_args(data->env);
	tmp[n] = NULL;
	return (tmp);
}

char	**u_export(t_data *data, char *args, int n)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = ft_calloc(n, sizeof(char *));
	if (!tmp)
		return (NULL);
	n = 0;
	while (data->export[j] != NULL)
	{
		if (ft_memcmp(data->export[j], args,
				ft_find_len(data->export[j])) != 0)
		{
			tmp[n] = ft_strdup(data->export[j]);
			j++;
			n++;
		}
		else
			j++;
	}
	clear_args(data->export);
	tmp[n] = NULL;
	return (tmp);
}

void	unset_export(t_data *data, t_exec *node)
{
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 0;
	j = 0;
	while (data->export[n] != NULL)
		n++;
	while (node->args[i] != NULL)
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_memcmp(data->export[j], node->args[i],
					ft_find_len(data->export[j])) == 0)
			{
				data->export = u_export(data, node->args[i], n);
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void	unset_env(t_data *data, t_exec *node)
{
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 0;
	j = 0;
	while (data->env[n] != NULL)
		n++;
	while (node->args[i] != NULL)
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_memcmp(data->env[j], node->args[i],
					ft_find_len(data->env[j])) == 0)
			{
				data->env = u_env(data, node->args[i], n);
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void	cmd_unset(t_data *data, t_exec *node)
{
	if (data->env)
	{
		if (node->args[1] && node->args[1][0] != '-')
		{
			unset_env(data, node);
			unset_export(data, node);
		}
	}
}
