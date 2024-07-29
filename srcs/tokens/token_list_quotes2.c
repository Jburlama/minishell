/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_quotes2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:31:35 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/19 10:27:32 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		panic("calloc faild!\n", data);
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
	if (rl_line_buffer[*i] == 34)
		add_token(data, i, DQUOTES);
	else if (rl_line_buffer[*i] == 39)
		add_token(data, i, SQUOTES);
	else if (is_special(rl_line_buffer[*i]))
		add_token(data, i, SPECIAL);
	else if (ft_isprint(rl_line_buffer[*i]) && rl_line_buffer[*i] != 32)
	{
		if (data->head
			&& (*data->tail->content == '<' || *data->tail->content == '>'))
			add_token(data, i, IO);
		else
			add_token(data, i, WORD);
	}
	else if (data->head && is_white_space(rl_line_buffer[*i]))
		add_token(data, i, WHITE_SPACE);
}

void	promp_quotes(char q)
{
	char	*line;

	line = NULL;
	if (q == 34)
		line = readline(YELLOW"dquote>"RESET);
	else if (q == 39)
		line = readline(YELLOW"quote>"RESET);
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	free(line);
}
