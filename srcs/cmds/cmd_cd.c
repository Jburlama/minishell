/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:56 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/08 13:00:45 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *pwd, t_data *data)
{
	update_env_pwd(pwd, data->env);
	update_env_pwd(pwd, data->export);
}

void	update_env_pwd(char *pwd, char **data_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "PWD=", 4) == 0)
		{
			tmp = ft_strdup(data_env[i] + 4);
			free(data_env[i]);
			data_env[i] = ft_strjoin("PWD=", pwd);
		}
		i++;
	}
	i = 0;
	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "OLDPWD=", 7) == 0)
		{
			free(data_env[i]);
			data_env[i] = ft_strjoin("OLDPWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

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
	}
	update_pwd(home, data);
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
		dir = get_last_dir(dir, data);
		if (dir)
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
		update_env_relative(node->args[1], data);
	}
}
