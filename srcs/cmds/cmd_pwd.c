/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/08 11:15:41 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	cmd_pwd(t_data *data, t_exec *node)
{
	char	*pwd;

	if (node->args[1] == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd != NULL)
			ft_printf("%s\n", pwd);
		else
		{
			data->builtin_fail = true;
			perror("pwd error");
		}
		free(pwd);
	}
	else
	{
		write (2, "pwd: ", 5);
		write (2, node->args[1], ft_strlen(node->args[1]));
		write (2, " invalid option\n", 16);
		data->exit_code = 2;
	}
}

int	ft_find_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			break ;
		}
		i++;
	}
	return (i);
}
