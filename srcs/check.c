/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:46:48 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/29 19:11:47 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i++;
			while (str[i])
			{
				if (str[i] == 34 || str[i] == 39)
					break ;
				i++;
			}
			if (str[i] == '\0')
				return (1);
		}
		if (str[i] == '!' || str[i] == '#' || str[i] == '&' || str[i] == '\\'
			|| str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}'
			|| str[i] == ';')
				return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] && str[i + 2])
	{
		if((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
		{
			printf("%s", RED"minishell: syntax error near unexpected token\n"RESET);
			return ;
		}
		i++;
	}
	check_heredoc(str, data);
	printf("%s", RED"minishell: syntax error near unexpected token\n"RESET);
}

void	check_redirect(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 60 || str[i] == 62)
		{
			if (str[i + 1] == 60 || str[i + 1] == 62)
				;
			else
				i++;
			while (str[i] != '\0')
			{
				if (str[i] != ' ')
					break ;
				i++;
			}
			if (str[i] == '\0')
			{
				data->exit_code = 2;
				i--;
			}
		}
		i++;
	}
}

int	check(char *str, t_data *data)
{
	int	i;

	i = 0;
	check_parentheses(str, data);
	check_redirect(str, data);
	if (!check_special(str))
		data->exit_code = 2;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' && str[i + 1] == '|')
			|| (str[i] == '<' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '|')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0')
			|| (str[i] == '|' && str[i + 1] == '\0')
			|| (str[i] == '$' && str[i + 1] == '$'))
			data->exit_code = 2;
		i++;
	}
	if (data->exit_code == 2)
	{
		ft_exit(str, data);
		return (data->exit_code);
	}
	return (0);
}
