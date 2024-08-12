/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:56:58 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/12 12:56:06 by vbritto-         ###   ########.fr       */
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

void	*here_doc_check(char *eof)
{
	char	*line;
	int		fd;

	fd = open("fail", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line
			|| ft_memcmp(line, eof, ft_strlen(eof) + 1) == 0)
			break ;
	}
	close(fd);
	return (NULL);
}

char	*find_eof(char *str, int *i, t_data *data)
{
	char	*eof;
	int		j;

	eof = NULL;
	j = *i;
	while (str[j] != '\0')
	{
		if (str[j] == ' ')
			break ;
		j++;
	}
	eof = ft_calloc((j - (*i)) + 1, sizeof(char));
	if (!eof)
		panic("erro", data);
	ft_strlcpy(eof, str + (*i), (j - (*i)) + 1);
	eof[j - (*i)] = '\0';
	*i = j;
	return (eof);
}

void	check_heredoc(char *str, t_data *data)
{
	char	*eof;
	int		i;

	i = 0;
	if (str[i] && str[i + 1] && str[i + 2])
	{
		while (str[i] != '\0')
		{
			if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == ' ')
				|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == ' '))
			{
				i += 3;
				eof = find_eof(str, &i, data);
				here_doc_check(eof);
				free (eof);
			}
			else
				i++;
		}
	}
}
