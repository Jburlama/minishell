/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_quotes2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:31:35 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/30 20:31:51 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_promp_for_quotes(t_data *data, char q, int len)
{
	int		new_len;
	int		j;
	char	*new_content;

	promp_quotes(q);
	j = 0;
	new_len = len;
	while (rl_line_buffer[j] && rl_line_buffer[j] != q)
	{
		j++;
		new_len++;
	}
	new_content = ft_calloc(sizeof(char), new_len + 1);
	if (!new_content)
		exit (1);
	ft_memcpy(new_content, data->tail->content, len);
	free(data->tail->content);
	data->tail->content = new_content;
	j = 0;
	while (rl_line_buffer[j] && rl_line_buffer[j] != q)
		data->tail->content[len++] = rl_line_buffer[j++];
	if (!rl_line_buffer[j])
		new_promp_for_quotes(data, q, new_len);
	tokenize_continue(data, q, &j);
}

void	tokenize_continue(t_data *data, char q, int *i)
{
	if (rl_line_buffer[*i] == q)
		(*i)++;
	if (!rl_line_buffer[*i])
		return ;
	while (is_white_space(rl_line_buffer[*i]))
		(*i)++;
	if (is_quote(rl_line_buffer[(*i)]))
		add_token(data, i, QUOTES);
	else if (is_special(rl_line_buffer[*i]))
		add_token(data, i, SPECIAL);
	else if (ft_isalpha(rl_line_buffer[*i]))
	{
		if (data->head
			&& (data->tail->type == WORD || data->tail->type == QUOTES))
			add_token(data, i, ARG);
		else
			add_token(data, i, WORD);
	}
}

void	promp_quotes(char q)
{
	if (q == 34)
		readline(YELLOW"dquote>"RESET);
	else if (q == 39)
		readline(YELLOW"quote>"RESET);
}
