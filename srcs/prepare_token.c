/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:59:57 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/13 18:53:49 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
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
}*/
int	ft_tokensize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
void	prepare_token(t_data *data)
{
	char 	*new_content;
	t_token	*tmp;
	t_token *keep;

	tmp = data->head;
	keep = tmp;
	while (tmp->next)
	{
		if ((tmp->type != DQUOTES && tmp->type != SQUOTES) &&
				(tmp->next->type == DQUOTES || tmp->next->type == SQUOTES))
			keep = tmp;
		if ((tmp->type == DQUOTES || tmp->type == SQUOTES)
			&& (tmp->next->type == DQUOTES || tmp->next->type == SQUOTES))
		{
			if (ft_tokensize(tmp) == 2)
			{
				new_content = ft_strjoin(tmp->content, tmp->next->content);
				free(tmp->content);
				tmp->content = new_content;
				free(tmp->next->content);
				free(tmp->next);
				tmp->next = NULL;
			}
			else
			{
				new_content = ft_strjoin(tmp->content, tmp->next->content);
				free(tmp->next->content);
				tmp->next->content = new_content;
				keep->next = tmp->next;
				free(tmp->content);
				free(tmp);
				tmp = keep;
			}
		}
		else
			tmp = tmp->next;
	}
}
