/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:32:49 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/30 21:33:16 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token_word(t_data *data, int *i, enum e_type type)
{
	if (!data->head)
		create_token_word(data, i, type);
	else
		append_token_word(data, i, type);
}

void	create_token_word(t_data *data, int *i, enum e_type type)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	while (ft_isprint(rl_line_buffer[j]) && rl_line_buffer[j] != 32)
	{
		j++;
		len++;
	}
	data->head = ft_calloc(sizeof(t_token), 1);
	if (!data->head)
		panic("calloc faild!\n", data);
	data->head->content = ft_calloc(sizeof(char), len + 1);
	if (!data->head->content)
		panic("calloc faild!\n", data);
	j = 0;
	while (ft_isprint(rl_line_buffer[*i]) && rl_line_buffer[*i] != 32)
		data->head->content[j++] = rl_line_buffer[(*i)++];
	data->head->type = type;
	data->tail = data->head;
	(*i)--;
}

void	append_token_word(t_data *data, int *i, enum e_type type)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	while (ft_isprint(rl_line_buffer[j]) && rl_line_buffer[j] != 32)
	{
		j++;
		len++;
	}
	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (!data->tail->next)
		panic("calloc faild!\n", data);
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), len + 1);
	if (data->tail->content == NULL)
		panic("calloc faild!\n", data);
	j = 0;
	while (ft_isprint(rl_line_buffer[*i]) && rl_line_buffer[*i] != 32)
		data->tail->content[j++] = rl_line_buffer[(*i)++];
	data->tail->type = type;
	(*i)--;
}

void	append_token_arg(t_data *data, int *i, enum e_type type)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	while (rl_line_buffer[j] && !is_special(rl_line_buffer[j])
		&& !is_quote(rl_line_buffer[j]))
	{
		len++;
		j++;
	}
	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (!data->tail->next)
		panic("calloc faild!\n", data);
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), len + 1);
	if (data->tail->content == NULL)
		panic("calloc faild!\n", data);
	j = 0;
	while (rl_line_buffer[*i] && !is_special(rl_line_buffer[*i])
		&& !is_quote(rl_line_buffer[*i]))
		data->tail->content[j++] = rl_line_buffer[(*i)++];
	data->tail->type = type;
	(*i)--;
}

void	add_token_special(t_data *data, int *i, enum e_type type)
{
	if (!data->head)
	{
		data->head = ft_calloc(sizeof(t_token), 1);
		if (!data->head)
			panic("calloc faild!\n", data);
		data->head->content = ft_calloc(sizeof(char), 2);
		if (!data->head->content)
			panic("calloc faild!\n", data);
		*data->head->content = rl_line_buffer[*i];
		data->head->next = NULL;
		data->head->type = type;
		data->tail = data->head;
		return ;
	}
	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (data->tail->next == NULL)
		panic("calloc faild!\n", data);
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), 2);
	if (data->tail->content == NULL)
		panic("calloc faild!\n", data);
	*data->tail->content = rl_line_buffer[*i];
	data->tail->type = type;
}
