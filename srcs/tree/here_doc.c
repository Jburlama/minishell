/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:44:50 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/08 11:20:26 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_here_doc(char *line, t_data *data)
{
	size_t	dol;

	dol = 0;
	while (line[dol] && line[dol + 1])
	{
		if ((line[dol] == '$')
			&& (line[dol + 1] >= 48 && line[dol + 1] <= 57))
		{
			dol++;
			line = expand_number(line, data, &dol);
		}
		else if (line[dol] == '$')
		{
			dol++;
			line = expand(line, data, &dol, 1);
			if (line == NULL)
				break ;
		}
		dol++;
	}
	return (line);
}

char	*here_doc(t_redir *root, char *eof, t_data *data)
{
	char	*line;
	int		fd;
	char	*file_name;

	file_name = open_heredoc_for_write(&fd);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line
			|| ft_memcmp(line, eof, ft_strlen(eof) + 1) == 0)
			break ;
		if (root->quote_type != SQUOTES && root->quote_type != DQUOTES)
			line = expand_here_doc(line, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	root->file_type = I;
	return (file_name);
}

char	*open_heredoc_for_write(int *fd)
{
	static int	n;
	char		*path;
	char		*file_name;
	char		*nbr;

	path = "/tmp/here_doc";
	file_name = NULL;
	while (42)
	{
		nbr = ft_itoa(n);
		file_name = ft_strjoin(path, nbr);
		*fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		free(nbr);
		if (*fd >= 0)
		{
			n++;
			break ;
		}
		free(file_name);
		n++;
	}
	return (file_name);
}
