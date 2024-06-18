/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_special.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:24:36 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/11 18:41:57 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token_special(t_data *data, int *i, enum e_type type)
{
	if (!data->head)
		create_token_special(data, i, type);
	else
		append_token_special(data, i, type);
	(*i)--;
}

void	create_token_special(t_data *data, int *i, enum e_type type)
{
	int	len;
	int	j;

	data->head = ft_calloc(sizeof(t_token), 1);
	if (!data->head)
		panic("calloc faild!\n", data);
	len = 0;
	if (rl_line_buffer[*i] == rl_line_buffer[*i + 1]
		&& rl_line_buffer[*i] != '(' && rl_line_buffer[*i] != ')')
		len = 2;
	else
		len = 1;
	data->head->content = ft_calloc(sizeof(char), len + 1);
	if (!data->head->content)
		panic("calloc faild!\n", data);
	j = 0;
	while (j < len)
		data->head->content[j++] = rl_line_buffer[(*i)++];
	data->head->next = NULL;
	data->head->type = type;
	data->tail = data->head;
}

void	append_token_special(t_data *data, int *i, enum e_type type)
{
	int	len;
	int	j;

	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (data->tail->next == NULL)
		panic("calloc faild!\n", data);
	len = 0;
	if (rl_line_buffer[*i] == rl_line_buffer[*i + 1]
		&& rl_line_buffer[*i] != '(' && rl_line_buffer[*i] != ')')
		len = 2;
	else
		len = 1;
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), len + 1);
	if (data->tail->content == NULL)
		panic("calloc faild!\n", data);
	j = 0;
	while (j < len)
		data->tail->content[j++] = rl_line_buffer[(*i)++];
	data->tail->type = type;
}
