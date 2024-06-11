/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:19:30 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/08 16:25:54 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_env(char **envp, char **my_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	my_env = ft_calloc(i, sizeof(char *));
	if (!my_env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		my_env[j] = ft_calloc(ft_strlen(envp[i]), sizeof(char));
		if (!my_env[j])
			return (NULL);
		ft_strlcpy(my_env[j], envp[i], ft_strlen(envp[i]));
		i++;
		j++;
	}
}

