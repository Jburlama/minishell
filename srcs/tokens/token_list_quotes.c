/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:11:20 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/30 21:32:07 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token_quotes(t_data *data, int *i, enum e_type type)
{
	enum e_type	file;

	file = 0;
	if (!data->head)
		create_token_quotes(data, i, type, rl_line_buffer[*i]);
	else
	{
		if (*data->tail->content == '<')
		{
			if (ft_strlen(data->tail->content) == 2)
				file = HERE_DOC;
			else
				file = I;
		}
		else if (*data->tail->content == '>')
		{
			if (ft_strlen(data->tail->content) == 2)
				file = APEND;
			else
				file = O;
		}
		append_token_quotes(data, i, type, rl_line_buffer[*i]);
		data->tail->file = file;
	}
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
		panic("calloc faild!\n", data);
	data->head->content = ft_calloc(sizeof(char), len + 1);
	if (!data->head->content)
		panic("calloc faild!\n", data);
	j = 0;
	while (rl_line_buffer[*i] && rl_line_buffer[*i] != q)
		data->head->content[j++] = rl_line_buffer[(*i)++];
	data->head->type = type;
	if (create_token_quotes2(data, i, q, len) == 1)
		return ;
}

int	create_token_quotes2(t_data *data, int *i, char q, int len)
{
	data->tail = data->head;
	if (rl_line_buffer[*i] == q)
		return (1);
	if (rl_line_buffer[(*i)] != q)
		new_promp_for_quotes(data, q, len);
	(*i) += len;
	return (0);
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
		panic("calloc faild!\n", data);
	j = 0;
	while (rl_line_buffer[*i] && rl_line_buffer[*i] != q)
		data->tail->content[j++] = rl_line_buffer[(*i)++];
	data->tail->type = type;
	if (rl_line_buffer[(*i)] != q)
		new_promp_for_quotes(data, q, len);
}
