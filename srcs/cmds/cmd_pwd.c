/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/20 12:07:45 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	**update_env_oldpwd(char *old_pwd, char **data_env, int i)
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
		data_env = export(data_env, old_pwd);
		free(tmp);
	}
	else
		data_env[i] = ft_strjoin("OLDPWD=", old_pwd);
	return (data_env);
}

char	**update_env_pwd(char *pwd, char **data_env, int i)
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
