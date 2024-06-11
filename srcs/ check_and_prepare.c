/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    check_and_prepare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:46:48 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/11 18:36:01 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes(char *str)
{
	int	i;

	i = 0;

		while (str[i] != '\0')
	{
		if (str[i] == 22)
		{
			while (str != '\0' || str[i] != 22)
				i++;
			if (str[i] == '\0')
				//Error bash: syntax error near unexpected token `newline
		}
		if (str[i] == 27)
		{
			while (str != '\0' || str[i] != 27)
				i++;
			if (str[i] == '\0')
				//Error bash: syntax error near unexpected token `newline
		}
		i++;
	}
}

void	check_heredoc(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '<' && str[i + 1] == '<')
			//here_doc
			//break
		else
			i++;
	}
}

void	check_redirect(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 20 && str[i] <= 127)
			i++;
		else
		//Error bash: syntax error near unexpected token `newline
	}
}

void	check(char *str)
{
	int	i;

	i = 0;
	check_quotes(str);
	check_heredoc(str);
	if (str[0] == '<' || str[0] == '>')
		check_redirect(str);
	while (str[i] != '\0')
	{
		if ((str[0] == '|') || (str[i] == '<' && str[i + 1] == '|'))
			//Error bash: syntax error near unexpected token `|'
		if ((str[i] == '<' && str[i + 1] == '\0') || (str[i] == '>' && str[i + 1] == '\0')
				|| str[i] == '>' && str[i + 1] == '|')
			//Error bash: syntax error near unexpected token `newline
	}
}
