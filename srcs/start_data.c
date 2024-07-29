/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:46:31 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/24 12:46:45 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**start_env(char **my_env, char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	my_env = ft_calloc(i + 1, sizeof(char *));
	if (!my_env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		my_env[j] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		if (!my_env[j])
			return (NULL);
		ft_strlcpy(my_env[j], envp[i], ft_strlen(envp[i]) + 1);
		i++;
		j++;
	}
	my_env[j] = NULL;
	return (my_env);
}

void	start_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(*data));
	data->env = start_env(data->env, envp);
	data->export = start_env(data->export, envp);
}
