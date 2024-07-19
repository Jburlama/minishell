/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:18:11 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/13 19:17:08 by vbritto-         ###   ########.fr       */
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
		dol++;
	}
	dol = 0;
	while (line[dol])
	{
		if (line[dol] == '$')
		{
			dol++;
			line = expand(line, data, &dol, 1);
		}
		dol++;
	}
	return (line);
}

void	here_doc(t_redir *root, t_data *data)
{
	char	*line;
	int		fd;
	char	*file_name;

	file_name = open_heredoc_for_write(&fd);
	dup2(STDERR_FILENO, STDIN_FILENO);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line
			|| ft_memcmp(line, root->file, ft_strlen(root->file) + 1) == 0)
			break ;
		if (root->quote_type != SQUOTES && root->quote_type != DQUOTES)
			line = expand_here_doc(line, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	open_heredoc_for_read(file_name, &fd);
}

char	*open_heredoc_for_write(int *fd)
{
	int		n;
	char	*path;
	char	*file_name;
	char	*nbr;

	n = 0;
	path = "/tmp/here_doc";
	file_name = NULL;
	while (42)
	{
		nbr = ft_itoa(n);
		file_name = ft_strjoin(path, nbr);
		*fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		free(nbr);
		if (*fd >= 0)
			break ;
		free(file_name);
		n++;
	}
	return (file_name);
}

void	open_heredoc_for_read(char *file_name, int *fd)
{
	if (access(file_name, F_OK) == 0)
	{
		*fd = open(file_name, O_RDWR);
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	free(file_name);
}
