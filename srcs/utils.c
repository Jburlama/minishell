/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:18:02 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/11 18:46:44 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_white_spaces(int *i)
{
	if (rl_line_buffer[(*i) + 1]
		&& is_white_space(rl_line_buffer[(*i) + 1]))
	{
		while (rl_line_buffer[(*i) + 1]
			&& is_white_space(rl_line_buffer[(*i) + 1]))
			(*i)++;
	}
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
