/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:56 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/20 14:37:33 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_last_dir(char *pwd)
{
	char	*last_dir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last_dir = NULL;
	while (pwd[i])
		i++;
	while (i != 0)
	{
		if (pwd[i] == '/')
			break ;
		i--;
	}
	last_dir = ft_calloc(i + 1, sizeof(char));
	if (!last_dir)
		return (NULL);
	while (j < i)
	{
		last_dir[j] = pwd[j];
		j++;
	}
	free(pwd);
	return (last_dir);
}

char	*get_home(char **env, t_data *data, t_exec *node)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_memcmp("HOME=", env[i], 5) == 0)
			home = env[i] + 5;
		i++;
	}
	if (home == NULL)
	{
		ft_printf("%s: %s\n", node->args[0],
			"HOME not set");
		data->exit_code = 1;
	}
	return (home);
}

void	cmd_cd(t_data *data, t_exec *node)
{
	char	*dir;

	if (!node->args[1]
		&& ft_memcmp("cd", node->args[0], ft_strlen(node->args[0])) == 0)
	{
		dir = get_home(data->env, data, node);
		chdir(dir);
	}
	else if (ft_memcmp("..", node->args[1], 2) == 0)
	{
		dir = getcwd(NULL, 0);
		dir = get_last_dir(dir);
		chdir(dir);
		free(dir);
	}
	else if (node->args[1])
	{
		if (*node->args[1] != '\0' && chdir(node->args[1]) != 0)
		{
			write(2, "cd: ", 4);
			perror(node->args[1]);
			data->exit_code = 1;
		}
	}
}
