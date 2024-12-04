/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:56 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/24 13:11:02 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_last_dir(char *pwd, t_data *data)
{
	char	*my_pwd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	my_pwd = NULL;
	if (data->env)
	{
		while (data->env[i])
		{
			if (ft_memcmp("PWD=", data->env[i], 4) == 0)
				my_pwd = ft_strdup(data->env[i] + 4);
			i++;
		}
		my_pwd = get_dir(my_pwd, data);
	}
	if (!my_pwd)
	{
		if (!pwd)
			return (NULL);
		my_pwd = get_dir(pwd, data);
	}
	return (my_pwd);
}

char	*get_dir(char *pwd, t_data *data)
{
	char	*last_dir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last_dir = NULL;
	if (!pwd)
		return (NULL);
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
	ft_strlcpy(last_dir, pwd, i + 1);
	update_pwd(last_dir, data);
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
		return (home);
	}
	update_pwd(home, data);
	return (home);
}

int	check_cd_args(t_exec *node, t_data *data)
{
	int	i;

	i = 0;
	while (node->args[i])
		i++;
	if (i <= 2)
		return (1);
	else
	{
		ft_printf("%s: %s\n", node->args[0], "too many arguments");
		data->exit_code = 1;
		return (0);
	}
}

void	cmd_cd(t_data *data, t_exec *node)
{
	char	*pwd;
	char	*dir;

	if (!check_cd_args(node, data))
		return ;
	if (!node->args[1]
		&& ft_memcmp("cd", node->args[0], ft_strlen(node->args[0])) == 0)
	{
		dir = get_home(data->env, data, node);
		chdir(dir);
	}
	else if (ft_memcmp("..", node->args[1], 2) == 0)
	{
		pwd = getcwd(NULL, 0);
		dir = get_last_dir(pwd, data);
		free(pwd);
		if (dir)
			chdir(dir);
		free(dir);
	}
	else if (node->args[1])
	{
		cd_relative(data, node);
		update_env_relative(node->args[1], data);
	}
}
