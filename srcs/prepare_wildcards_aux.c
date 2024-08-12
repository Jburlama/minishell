/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_wildcards_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:50:15 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/12 12:39:07 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_dot(char *wild, t_token *wild_node)
{
	int	i;
	int	j;

	i = ft_strlen(wild_node->content);
	if (wild)
	{
		j = ft_strlen(wild) - 1;
		if (i >= j && ft_memcmp(wild + 1, wild_node->content + (i - j),
				j) != 0)
			return (false);
	}
	return (true);
}

t_token	*ft_lasttoken(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (lst == NULL)
		return (lst);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	tokenize_wildcards(t_token *wildcards, t_token *before, t_token *tmp,
	t_data *data)
{
	t_token	*last_wild;

	last_wild = ft_lasttoken(wildcards);
	if (last_wild)
	{
		if (before == data->head)
			data->head = wildcards;
		else
		{
			if (before->next->next)
				last_wild->next = before->next->next;
			else
				last_wild->next = NULL;
			before->next = wildcards;
		}
		free(tmp->content);
		free(tmp);
	}
}
