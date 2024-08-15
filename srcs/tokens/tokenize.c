/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:02:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/08/15 15:36:10 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tokenize(t_data *data)
{
	int	i;

	i = 0;
	while (rl_line_buffer[i] <= 32 && rl_line_buffer[i] != '\0')
		i++;
	while (rl_line_buffer[i])
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
		if (data->tail
			&& (*data->tail->content == '>' || *data->tail->content == '<'))
		{
			jump_white_spaces(i);
			return ;
		}
		add_token_special(data, i, type);
		jump_white_spaces(i);
	}
	else if (type == WORD)
		add_token_word(data, i, type);
	else if (type == DQUOTES || type == SQUOTES)
		add_token_quotes(data, i, type);
	else if (type == IO)
		add_token_io(data, i);
	else if (type == WHITE_SPACE)
		add_token_white_space(data, i, type);
}

void	add_token_io(t_data *data, int *i)
{
	if (*data->tail->content == '<')
	{
		if (ft_strlen(data->tail->content) == 2)
			add_token_word(data, i, HERE_DOC);
		else
			add_token_word(data, i, I);
	}
	else if (*data->tail->content == '>')
	{
		if (ft_strlen(data->tail->content) == 2)
			add_token_word(data, i, APEND);
		else
			add_token_word(data, i, O);
	}
}
