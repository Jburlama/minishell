/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:09:47 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/11 12:18:52 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *pwd, t_data *data)
{
	update_env_pwd(pwd, data->env);
	update_env_pwd(pwd, data->export);
}

void	update_env_relative(char *pwd, t_data *data)
{
	int		i;
	char	*tmp;
	char	*old_pwd;

	i = 0;
	old_pwd = NULL;
	tmp = ft_strjoin("/", pwd);
	update_relative_pwd(tmp, data->env, i, old_pwd);
	update_relative_pwd(tmp, data->export, i, old_pwd);
	free(tmp);
}

void	update_relative_pwd(char *pwd, char **data_env, int i, char *old_pwd)
{
	char	*tmp;

	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "PWD=", 4) == 0)
		{
			old_pwd = ft_strdup(data_env[i] + 4);
			tmp = ft_strjoin(data_env[i], pwd);
			free(data_env[i]);
			data_env[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	i = 0;
	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "OLDPWD=", 7) == 0)
		{
			free(data_env[i]);
			data_env[i] = ft_strjoin("OLDPWD=", old_pwd);
			free(old_pwd);
		}
		i++;
	}
}

void	cd_relative(t_data *data, t_exec *node)
{
	if (*node->args[1] != '\0' && chdir(node->args[1]) != 0)
	{
		write(2, "cd: ", 4);
		perror(node->args[1]);
		data->exit_code = 1;
	}
}
