/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/11 12:15:55 by vbritto-         ###   ########.fr       */
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
