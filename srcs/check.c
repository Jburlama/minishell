/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:46:48 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/20 19:22:47 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*jump_quotes(char *str, int *parentheses)
{
	if ((str[parentheses[0]] == 34 || str[parentheses[0]] == 39))
	{
		parentheses[0]++;
		while (str[parentheses[0]] != '\0')
		{
			if ((str[parentheses[0]] == 34 || str[parentheses[0]] == 39))
				break ;
			parentheses[0]++;
		}
		parentheses[0]--;
	}
	if (str[parentheses[0]] == 40)
		parentheses[1]++;
	if (str[parentheses[0]] == 41)
		parentheses[1]--;
	if (parentheses[1] < 0)
		return (parentheses);
	return (parentheses);
}

void	check_parentheses(char *str, t_data *data)
{
	int	*parentheses;

	parentheses = ft_calloc(2, sizeof(int));
	while (str[parentheses[0]] != '\0')
	{
		parentheses = jump_quotes(str, parentheses);
		parentheses[0]++;
	}
	if (parentheses[1] != 0)
		data->exit_code = 2;
	free (parentheses);
}

void	check_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			//here_doc
			break ;
		else
			i++;
	}
}

void	ft_exit(char *str)
{
	check_heredoc(str);
	printf("%s", RED"minishell: syntax error near unexpected token\n"RESET);
}

void	check_redirect(char *str, t_data *data)
{
	int	i;
	int	l;
	int	r;

	i = 0;
	l = 0;
	r = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 32 && str[i] <= 127)
		{
			if (str[i] == 60)
				l++;
			if (str[i] == 62)
				r++;
			if (l > 3 || r > 2)
				data->exit_code = 2;
		}
		else
			data->exit_code = 2;
		i++;
	}
}

int	check(char *str, t_data *data)
{
	int	i;

	i = 0;
	check_parentheses(str, data);
	if (str[0] == 60 || str[0] == 62)
		//check_redirect(str, data);
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
		ft_exit(str);
		return (data->exit_code);
	}
	return (0);
}
//verificar " " apos >
