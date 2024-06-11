/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:59:57 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/11 14:41:05 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand(char *env_name, t_data *data)
{
	char	*name_expanded;

	env_name++;
	name_expanded = getenv(env_name);
	if (!name_expanded)
		return (env_name);
	env_name = ft_calloc(ft_strlen(name_expanded) + 1, sizeof(char));
	if (!env_name)
		panic("calloc_fail", &data);
	ft_strlcpy(env_name, name_expanded, ft_strlen(name_expanded));
	return (env_name);
}
