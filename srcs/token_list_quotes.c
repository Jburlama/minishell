/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:11:20 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/30 20:31:59 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token_quotes(t_data *data, int *i, enum e_type type)
{
	if (!data->head)
		create_token_quotes(data, i, type, rl_line_buffer[*i]);
	else
		append_token_quotes(data, i, type, rl_line_buffer[*i]);
}

void	create_token_quotes(t_data *data, int *i, enum e_type type, char q)
{
	int	j;
	int	len;

	(*i)++;
	j = *i;
	len = 0;
	while (rl_line_buffer[j] && rl_line_buffer[j] != q)
	{
		len++;
		j++;
	}
	data->head = ft_calloc(sizeof(t_token), 1);
	if (!data->head)
		exit(1);
	data->head->content = ft_calloc(sizeof(char), len + 1);
	if (!data->head->content)
		exit (1);
	j = 0;
	while (rl_line_buffer[*i] && rl_line_buffer[*i] != q)
		data->head->content[j++] = rl_line_buffer[(*i)++];
	data->tail = data->head;
	data->head->type = type;
	if (rl_line_buffer[(*i)] != q)
		new_promp_for_quotes(data, q, len);
	(*i) += len;
}

void	append_token_quotes(t_data *data, int *i, enum e_type type, char q)
{
	int	j;
	int	len;

	(*i)++;
	j = *i;
	len = 0;
	while (rl_line_buffer[j] && rl_line_buffer[j] != q)
	{
		len++;
		j++;
	}
	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (!data->tail->next)
		exit(1);
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), len + 1);
	if (data->tail->content == NULL)
		exit(1);
	j = 0;
	while (rl_line_buffer[*i] && rl_line_buffer[*i] != q)
		data->tail->content[j++] = rl_line_buffer[(*i)++];
	data->tail->type = type;
	if (rl_line_buffer[(*i)] != q)
		new_promp_for_quotes(data, q, len);
	(*i) += len;
}
