/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:16:54 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/11 17:30:57 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_wild_list(t_token *wild_list, t_token *wild_node)
{
	t_token	*tmp;

	tmp = wild_list;
	if (!wild_list)
		return (wild_node);
	while (wild_list->next != NULL)
		wild_list = wild_list->next;
	wild_list->next = wild_node;
	return (tmp);
}

t_token	*create_wild_node(char *name, char *wild, t_data *data)
{
	t_token	*wild_node;

	wild_node = NULL;
	if (name[0] != '.')
	{
		wild_node = ft_calloc(1, sizeof(t_token));
		if (!wild_node)
			panic("Calloc error", data);
		wild_node->content = ft_strdup(name);
		if (!check_dot(wild, wild_node))
		{
			free(wild_node->content);
			free(wild_node);
			return (NULL);
		}
		wild_node->type = WORD;
		wild_node->builtin = NO_B;
		wild_node->next = NULL;
		return (wild_node);
	}
	return (NULL);
}

void	*exp_wildcards(t_token *wild_list, char *wild, t_data *data)
{
	DIR				*dir;
	struct dirent	*ent;
	t_token			*wild_node;

	wild_node = NULL;
	ent = NULL;
	dir = opendir(".");
	if (dir)
	{
		ent = readdir(dir);
		while (ent)
		{
			wild_node = create_wild_node(ent->d_name, wild, data);
			if (wild_node)
			{
				wild_list = create_wild_list(wild_list, wild_node);
				wild_node = wild_node->next;
			}
			ent = readdir(dir);
		}
		free(ent);
		free(dir);
	}
	return (wild_list);
}

void	prepare_wildcards(t_data *data)
{
	t_token	*tmp;
	t_token	*before;
	t_token	*wildcards;

	tmp = data->head;
	before = tmp;
	while (tmp)
	{
		if (tmp->content[0] == '*')
		{
			wildcards = NULL;
			wildcards = exp_wildcards(wildcards, tmp->content, data);
			if (wildcards && !wildcards->content)
			{
				free(wildcards);
				return ;
			}
			tokenize_wildcards(wildcards, before, tmp, data);
			tmp = wildcards;
		}
		before = tmp;
		if (tmp)
			tmp = tmp->next;
	}
}
