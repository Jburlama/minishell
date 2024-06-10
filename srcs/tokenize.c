/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:02:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/10 20:57:46 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize(t_data *data)
{
	int	i;

	i = 0;
	while (rl_line_buffer[i] && rl_line_buffer[i] != '#')
	{
		if (rl_line_buffer[i] == 34)
			add_token(data, &i, DQUOTES);
		else if (rl_line_buffer[i] == 39)
			add_token(data, &i, SQUOTES);
		else if (is_special(rl_line_buffer[i]))
			add_token(data, &i, SPECIAL);
		else if (ft_isprint(rl_line_buffer[i]) && rl_line_buffer[i] != 32)
		{
			if (data->head
				&& (*data->tail->content == '<' || *data->tail->content == '>'))
				add_token(data, &i, IO);
			else
				add_token(data, &i, WORD);
		}
		else if (rl_line_buffer[i] && is_white_space(rl_line_buffer[i]))
			add_token(data, &i, WHITE_SPACE);
		i++;
	}
}

void	add_token(t_data *data, int *i, enum e_type type)
{
	if (type == SPECIAL)
	{
		add_token_special(data, i, type);
		if (rl_line_buffer[(*i) + 1]
			&& is_white_space(rl_line_buffer[(*i) + 1]))
		{
			while (rl_line_buffer[(*i) + 1]
				&& is_white_space(rl_line_buffer[(*i) + 1]))
				(*i)++;
		}
	}
	else if (type == WORD)
		add_token_word(data, i, type);
	else if (type == DQUOTES || type == SQUOTES)
		add_token_quotes(data, i, type);
	else if (type == IO)
	{
		if (*data->tail->content == '<')
			add_token_word(data, i, I);
		else if (*data->tail->content == '>')
			add_token_word(data, i, O);
	}
	else if (type == WHITE_SPACE)
		add_token_white_space(data, i, type);
}

void	clear_list(t_token	**head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		*head = (*head)->next;
		free(temp->content);
		free(temp);
		temp = *head;
	}
	*head = NULL;
}

bool	is_special(char c)
{
	char	*special;
	int		i;

	special = "|<>";
	i = 0;
	while (special[i])
	{
		if (c == special[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (true);
	else
		return (false);
}
