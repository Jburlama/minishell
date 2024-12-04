/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:09:47 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/20 11:49:31 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *pwd, t_data *data)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = getcwd(NULL, 0);
	data->env = update_env_pwd(pwd, data->env, i);
	data->export = update_env_pwd(pwd, data->export, i);
	data->env = update_env_oldpwd(old_pwd, data->env, i);
	data->export = update_env_oldpwd(old_pwd, data->export, i);
	free(old_pwd);
}

void	update_env_relative(char *pwd, t_data *data)
{
	int		i;
	char	*old_pwd;

	i = ft_strlen(pwd);
	pwd = getcwd(NULL, 0);
	old_pwd = ft_calloc(ft_strlen(pwd) - i + 1, sizeof(char *));
	if (!old_pwd)
		panic("calloc_fail", data);
	ft_strlcpy(old_pwd, pwd, (ft_strlen(pwd) - i + 1));
	i = 0;
	data->env = update_relative_pwd(pwd, data->env, i);
	data->export = update_relative_pwd(pwd, data->export, i);
	data->env = update_relative_oldpwd(old_pwd, data->env, i);
	data->export = update_relative_oldpwd(old_pwd, data->export, i);
	free(old_pwd);
	free(pwd);
}

char	**update_relative_pwd(char *pwd, char **data_env, int i)
{
	char	*tmp;

	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "PWD=", 4) == 0)
		{
			free(data_env[i]);
			break ;
		}
		i++;
	}
	if (data_env[i] == NULL)
	{
		tmp = ft_strjoin("PWD=", pwd);
		data_env = export(data_env, tmp);
		free(tmp);
	}
	else
		data_env[i] = ft_strjoin("PWD=", pwd);
	return (data_env);
}

char	**update_relative_oldpwd(char *old_pwd, char **data_env, int i)
{
	char	*tmp;

	while (data_env[i])
	{
		if (ft_memcmp(data_env[i], "OLDPWD=", 7) == 0)
		{
			free(data_env[i]);
			break ;
		}
		i++;
	}
	if (data_env[i] == NULL)
	{
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		data_env = export(data_env, tmp);
		free(tmp);
	}
	else
		data_env[i] = ft_strjoin("OLDPWD=", old_pwd);
	return (data_env);
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
