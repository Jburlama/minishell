/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:00 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/20 13:12:33 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prepare_builtins(t_data *data)
{
	t_token	*tmp;

	tmp = data->head;
	while (tmp)
	{
		if (ft_memcmp("echo", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = ECHO;
		else if (ft_memcmp("cd", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = CD;
		else if (ft_memcmp("pwd", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = PWD;
		else if (ft_memcmp("export", tmp->content,
				ft_strlen(tmp->content)) == 0)
			tmp->builtin = EXPORT;
		else if (ft_memcmp("unset", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = UNSET;
		else if (ft_memcmp("exit", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = EXIT;
		else
			tmp->builtin = NO_B;
		tmp = tmp->next;
	}
}

t_token	*handle_quotes_aux(t_token *tmp, t_token *keep)
{
	char	*new_content;

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
		free(tmp->next->content);
		tmp->next->content = new_content;
		keep->next = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = keep->next;
	}
	return (tmp);
}

void	handle_first_quote(t_token *tmp, t_token *keep, int first_quote)
{
	char	*new_content;

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

void	handle_quotes(t_data *data)
{
	t_token	*tmp;
	t_token	*keep;
	int		first_quote;

	first_quote = 0;
	tmp = data->head;
	keep = tmp;
	if (((tmp->type == 3 || tmp->type == 4) && tmp->next
			&& tmp->next->type != 2) || (tmp->next && (tmp->type != 2
				&& (tmp->next->type == 3 || tmp->next->type == 4))))
		first_quote = 1;
	while (tmp && tmp->next)
	{
		if (tmp->next->type && tmp->next->type == WHITE_SPACE)
			first_quote = 0;
		if (first_quote == 1 && tmp->type != 2)
			handle_first_quote(tmp, keep, first_quote);
		else if ((tmp->type == DQUOTES || tmp->type == SQUOTES
				|| tmp->next->type == DQUOTES || tmp->next->type == SQUOTES)
			&& (tmp->type != WHITE_SPACE) && (tmp->next->type != WHITE_SPACE)
			&& (tmp->type != SPECIAL && tmp->next->type != SPECIAL))
			tmp = handle_quotes_aux(tmp, keep);
		else
			tmp = tmp->next;
	}
}

void	prepare_token(t_data *data)
{
	if (data->head
		&& data->head->content[0] == '\0' && data->head->next == NULL)
		return ;
	if (data->head)
	{
		prepare_dollar(data);
		if (data->head)
		{
			prepare_wildcards(data);
			handle_quotes(data);
			prepare_builtins(data);
			find_null(data);
		}
	}
}
