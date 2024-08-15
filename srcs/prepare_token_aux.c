/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_token_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:29:11 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/15 18:31:55 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_block(t_data *data)
{
	t_token	*tmp;
	size_t	i;

	tmp = data->head;
	while (tmp)
	{
		i = ft_strlen(tmp->content);
		if ((tmp->content[i - 1] == ')')
			&& (tmp->type != SQUOTES && tmp->type != DQUOTES))
		{
			if (tmp->next && tmp->next->type != SPECIAL)
			{
				write (2, "minishell: ambiguous redirect\n", 30);
				data->exit_code = 1;
				clear_list(data);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	find_null(t_data *data)
{
	t_token	*tmp;

	tmp = data->head;
	while (tmp)
	{
		if (tmp->type == 2
			&& ((tmp->content[0] == '>' && tmp->content[1] == '\0')
				|| (tmp->content[0] == '<' && tmp->content[1] == '\0')))
		{
			tmp = tmp->next;
			while (tmp && tmp->next && tmp->type == WHITE_SPACE)
				tmp = tmp->next;
			if (!tmp)
			{
				write (2, "minishell: ambiguous redirect\n", 30);
				data->exit_code = 1;
				clear_list(data);
				return ;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	find_block(data);
}

int	ft_isexp(int c)
{
	if ((c >= '0' && c <= '9') || (c == '?'))
		return (2048);
	else
		return (0);
}

void	check_dquotes(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] == 39)
					break ;
				i++;
			}
			if (str[i] == '\0')
			{
				data->exit_code = 2;
				i--;
			}
			check_quotes(str + i, data);
		}
		i++;
	}
}

void	check_quotes(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] == 34)
					break ;
				i++;
			}
			if (str[i] == '\0')
			{
				data->exit_code = 2;
				i--;
			}
			check_dquotes(str + i, data);
		}
		i++;
	}
}
