/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/10 13:21:26 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_pwd(t_data *data)
{
	char	*pwd;

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
