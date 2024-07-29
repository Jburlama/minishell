/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:04:55 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/14 18:22:45 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	runexec(t_exec *node, t_data *data)
{
	char	*pathname;

	if (node->args[0])
	{
		pathname = get_pathname(node->args[0], data->env);
		if (pathname == NULL)
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
	clear_tree(data->root);
	exit(errno);
}

char	*get_pathname(char	*name, char **env)
{
	int		i;
	char	*temp;
	char	*pathname;
	char	**paths;

	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	paths = get_paths(env);
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

char	**get_paths(char **env)
{
	int		i;
	char	*paths;
	char	**paths_arr;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_memcmp("PATH=", env[i], 5) == 0)
			paths = env[i] + 5;
		i++;
	}
	paths_arr = ft_split(paths, ':');
	return (paths_arr);
}
