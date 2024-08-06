/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:04:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/19 09:56:31 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	runexec(t_exec *node, t_data *data)
{
	char	*pathname;

	if (node->builtin != NO_B)
		execute_builtins(node, data);
	else
	{
		if (node->args[0])
		{
			pathname = get_pathname(node->args[0], data->env, data);
			if (pathname == NULL && data->env)
				perror(node->args[0]);
		}
		else
			pathname = NULL;
		if (pathname)
		{
			execve(pathname, node->args, data->env);
			free(pathname);
			perror(node->args[0]);
		}
	}
	clear_end_run_exec(data);
}

void	clear_end_run_exec(t_data *data)
{
	clear_args(data->env);
	clear_args(data->export);
	clear_tree(data->root);
	if (errno == 13)
		exit(126);
	exit(127);
}

char	*get_pathname(char	*name, char **env, t_data *data)
{
	int		i;
	char	*temp;
	char	*pathname;
	char	**paths;

	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	paths = get_paths(env, data);
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (name[0])
			pathname = ft_strjoin(temp, name);
		else
			pathname = ft_strjoin(temp, " ");
		free(temp);
		if (access(pathname, X_OK) == 0)
			return (clear_args(paths), pathname);
		free(pathname);
	}
	return (clear_args(paths), NULL);
}

char	**get_paths(char **env, t_data *data)
{
	int		i;
	char	*paths;
	char	**paths_arr;

	i = 0;
	paths = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_memcmp("PATH=", env[i], 5) == 0)
			paths = env[i] + 5;
		i++;
	}
	if (paths == NULL)
	{
		write(2, "env: command not found\n", 23);
		clear_end_run_exec(data);
		exit(127);
	}
	paths_arr = ft_split(paths, ':');
	return (paths_arr);
}
