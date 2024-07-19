/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:09:39 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/19 10:13:56 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export(t_exec *node, char *args, int j)
{
	int	i;

	i = 0;
	if (node->args [j + 1] && node->args[j + 1][0] == '=')
	{
		ft_printf ("%s%s%s\n", RED"minishell: export: `",
			node->args[j + 1], "' : not a valid identifier"RESET);
		if ((ft_chrcount(node->args[j + 2], '=') == 0) && node->args[j + 2])
			ft_printf ("%s%s%s\n", RED"minishell: export: `",
				node->args[j + 2], "' : not a valid identifier"RESET);
		return (1);
	}
	while (args[i])
	{
		if ((!ft_isalpha(args[0]))
			|| (args[i] == '=' && !is_export(args[i - 1])))
		{
			ft_printf ("%s%s%s\n", RED"minishell: export: `",
				node->args[j], "' : not a valid identifier"RESET);
			return (0);
		}
		i++;
	}
	return (2);
}

void	equal_or_plus_chg(char *arg, char **old_env, int i, int j)
{
	char	*tmp;

	if (arg[i] == '+' && arg[i + 1] && arg[i + 1] == 61)
	{
		tmp = ft_strjoin(old_env[j], arg + i + 2);
		free (old_env[j]);
		old_env[j] = ft_strdup(tmp);
		free (tmp);
	}
	else
	{
		free (old_env[j]);
		old_env[j] = ft_strdup(arg);
	}
}

int	equal_or_plus(char **old_env, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' || arg[i] == '+')
			break ;
		i++;
	}
	if (arg[i] != '\0')
	{
		while (old_env[j])
		{
			if (ft_memcmp(arg, old_env[j], i) == 0)
			{
				equal_or_plus_chg(arg, old_env, i, j);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

char	**export(char **old_env, char *arg)
{
	char	**new_env;
	int		i;

	i = 0;
	if (equal_or_plus(old_env, arg))
		return (old_env);
	while (old_env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i] != NULL)
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	clear_args(old_env);
	return (new_env);
}

void	cmd_export(t_data *data, t_exec *node)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (just_export(data, node))
		return ;
	while (node->args[j])
	{
		i = check_export(node, node->args[j], j);
		if (i == 1)
		{
			data->export = export(data->export, node->args[j]);
			if ((ft_chrcount(node->args[j + 2], '=') == 0) && node->args[j + 2])
				j++;
			j++;
		}
		else if (i == 2)
		{
			if (ft_chrcount(node->args[j], '=') != 0)
				data->env = export(data->env, node->args[j]);
			data->export = export(data->export, node->args[j]);
		}
		j++;
	}
}
