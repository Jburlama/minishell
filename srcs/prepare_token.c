/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:59:57 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/17 14:09:11 by vbritto-         ###   ########.fr       */
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

t_token	*handle_quotes(t_token *tmp, t_token *keep)
{
	char 	*new_content;

	new_content = ft_strjoin(tmp->content, tmp->next->content);
	free(tmp->next->content);
	tmp->next->content = new_content;
	keep->next = tmp->next;
	free(tmp->content);
	free(tmp);
	return (keep);
}

void	handle_first_quote(t_token *tmp, t_token *keep, int first_quote)
{	
	char 	*new_content;

	new_content = ft_strjoin(tmp->content, tmp->next->content);
	if (!tmp->next->next)
	{
		free(tmp->content);
		tmp->content = new_content;
		free(tmp->next->content);
		free(tmp->next);
		tmp->next = NULL;
	}
	else
	{
		free(tmp->content);
		tmp->content = new_content;
		tmp = tmp->next;
		keep->next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = keep;
	}
	if (tmp->next && tmp->next->type != SQUOTES && tmp->next->type != DQUOTES)
		first_quote = 0;
}

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
	t_token	*tmp;
	t_token	*keep;
	int		first_quote;

	first_quote = 0;
	tmp = data->head;
	keep = tmp;
	if (tmp->type == DQUOTES || tmp->type == SQUOTES)
		first_quote = 1;
	while (tmp && tmp->next)
	{
		if (tmp->type != DQUOTES && tmp->type != SQUOTES)
			keep = tmp;
		if ((tmp->type == DQUOTES || tmp->type == SQUOTES)
			&& (tmp->next->type == DQUOTES || tmp->next->type == SQUOTES))
		{
			if (first_quote == 1)
				handle_first_quote(tmp, keep, first_quote);
			else
				tmp = handle_quotes(tmp, keep);
		}
		else
			tmp = tmp->next;
	}
}
