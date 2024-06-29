/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:01:44 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/29 15:30:04 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_printf("%s\n", pwd);
	else
		perror("pwd error");
}
