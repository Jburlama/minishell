/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:02:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/29 19:52:19 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize(t_data *data)
{
	int i;

	i = 0;
	while (rl_line_buffer[i])
	{
		if (is_special(rl_line_buffer[i]))
			add_token(data, &i, SPECIAL);
		i++;
	}
}

void	add_token(t_data *data, int *i, enum e_type type)
{
	if (!data->head)
	{
		data->head = ft_calloc(sizeof(t_token), 1);
		if (!data->head)
			exit(1);
		data->head->content = ft_calloc(sizeof(char), 2);
		if (!data->head->content)
			exit (1);
		*data->head->content = rl_line_buffer[*i];
		data->head->next = NULL;
		data->head->type = type;
		data->tail = data->head;
		return ;
		// (*i)++;
	}
	data->tail->next = ft_calloc(sizeof(t_token), 1);
	if (data->tail->next == NULL)
		exit (1);
	data->tail = data->tail->next;
	data->tail->content = ft_calloc(sizeof(char), 2);
	if (data->tail->content == NULL)
		exit (1);
	*data->tail->content = rl_line_buffer[*i];
	data->tail->next = NULL;
	data->tail->type = type;
	// (*i)++;
}

void	clear_list(t_token	**head)
{
	t_token *temp;

	temp =  *head;
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

	special = "|<>;";
	i = 0;
	while (special[i])
	{
		if (c == special[i])
			return (true);
		i++;
	}
	return (false);
}
