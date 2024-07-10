/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:46:48 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/10 13:22:14 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	check_parentheses(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while(str[i] != 34 && str[i] != 39)
		{
			if (str[i] == 40)
 		}

	}

}*/

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

void	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != '\0' && str[i] != 34)
				i++;
			if (str[i] == '\0')
				status_exit = 2;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != '\0' && str[i] != 39)
				i++;
			if (str[i] == '\0')
				status_exit = 2;
		}
		i++;
	}
}

void	check_redirect(char *str)
{
	int	i;
	int	l;
	int	r;

	i = 0;
	l = 0;
	r = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 32 && str[i] <= 127)
		{
			if (str[i] == 60)
				l++;
			if (str[i] == 62)
				r++;
			if (l > 3 || r > 2)
				status_exit = 2;
		}
		else
			status_exit = 2;
		i++;
	}
}

int	check(char *str)
{
	int	i;

	i = 0;
	check_quotes(str);
	//check_parentheses(str);
	if (str[0] == 60 || str[0] == 62)
		check_redirect(str);
	while (str[i] != '\0')
	{
		if ((str[i] == '<' && str[i + 1] == '|')
			|| (str[i] == '<' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '\0')
			//|| (str[i] == '>' && str[i + 1] == '|')
			|| (str[i] == '|' && str[i + 1] == '\0')
			|| (str[i] == '$' && str[i + 1] == '$'))
			status_exit = 2;
		i++;
	}
	if (status_exit == 2)
	{
		ft_exit(str);
		return (status_exit);
	}
	return (0);
}
//tratar () erro
//verificar " " apos >