/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:18:11 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/17 15:46:57 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*here_doc(t_redir *root, char *eof)
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
