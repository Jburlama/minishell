/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:00 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/18 16:55:12 by vbritto-         ###   ########.fr       */
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

void	prepare_builtins(t_data *data)
{
	t_token	*tmp;

	tmp = data->head;
	while (!tmp)
	{
		if (ft_memcmp("echo", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = ECHO;
		else if (ft_memcmp("cd", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = CD;
		else if (ft_memcmp("pwd", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = PWD;
		else if (ft_memcmp("export", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = EXPORT;
		else if (ft_memcmp("unset", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = UNSET;
		else if (ft_memcmp("env", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = ENV;
		else if (ft_memcmp("exit", tmp->content, ft_strlen(tmp->content)) == 0)
			tmp->builtin = EXIT;
		else
			tmp->builtin = NO_B;
		tmp = tmp->next;
	}
}



t_token	*handle_quotes_aux(t_token *tmp, t_token *keep)
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

void	handle_quotes(t_data *data)
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
			&& (tmp->next->type != WHITE_SPACE))
		{
			if (first_quote == 1)
				handle_first_quote(tmp, keep, first_quote);
			else
				tmp = handle_quotes_aux(tmp, keep);
		}
		else
			tmp = tmp->next;
	}
}

void	prepare_token(t_data *data)
{
	if (data->head)
	{
		prepare_dollar(data);
		prepare_builtins(data);
		handle_quotes(data);
	}
}