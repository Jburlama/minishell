/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:46:48 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/15 18:51:45 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_parentheses(char *str, t_data *data)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			while (str[i + 1] != '\0')
			{
				if ((str[i + 1] == 34 || str[i + 1] == 39))
					break ;
			i++;
			}
 		}
		if (str[i] == 40)
		{
			while (str[i] != '\0')
			{
				if (str[i] == 40)
					j++;
				if (str[i] == 41)
					z++;
				i++;
			}
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
	if (z != j)
		data->error_code = 2;
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
	ft_printf("%s", RED"minishell: syntax error near unexpected token\n"RESET);
	check_heredoc(str);
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
				data->error_code = 2;
		}
		else
			data->error_code = 2;
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
			//|| (str[i] == '>' && str[i + 1] == '|')
			|| (str[i] == '|' && str[i + 1] == '\0')
			|| (str[i] == '$' && str[i + 1] == '$'))
			data->error_code = 2;
		i++;
	}
	if (data->error_code == 2)
	{
		ft_exit(str);
		return (data->error_code);
	}
	return (0);
}
//tratar () erro
//verificar " " apos >



// erro demonio -> pwd && (echo 123 | echo 123) ls  && cd ..