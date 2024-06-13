/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:54:50 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 20:24:53 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(t_data *data)
{
	if (data->root)
		rumcmd(data->root, data);
	exit(errno);
}

void	rumcmd(void *root, t_data *data)
{
	if (((t_exec *)root)->type == EXEC)
		rumexec(root, data);
}

void	rumexec(t_exec *node, t_data *data)
{
	char	*pathname;

	pathname = get_pathname(node->args[0], data->env);
	if (pathname)
	{
		execve(pathname, node->args, data->env);
		free(pathname);
	}
	clear_tree(data->root);
	perror("");
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
		pathname = ft_strjoin(temp, name);
		free(temp);
		if (access(pathname, X_OK) == 0)
		{
			clear_args(paths);
			return (pathname);
		}
		free(pathname);
	}
	clear_args(paths);
	return (NULL);
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
