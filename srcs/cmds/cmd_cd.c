/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:56 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/29 15:44:28 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_memcmp("HOME=", env[i], 5) == 0)
			home = env[i] + 5;
		i++;
	}
	return (home);
}

void	cmd_cd(t_data *data, t_exec *node)
{
	char	*home;

	home = get_home(data->env);
	if (ft_memcmp("cd", node->args[1], ft_strlen(node->args[1])) == 0)
		chdir(home);
	//clear_tree(data->root);
	//exit(status_exit);
}