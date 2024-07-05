/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:18:11 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/05 18:32:06 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc(t_redir *root, t_data *data)
{
	char	*line;
	char	*heredoc_file;
	int		fd;

	fd = -1;
	while (fd < 0)
	{
		heredoc_file = get_heredoc_file_name(data);
		fd = open(heredoc_file, O_CREAT | O_APPEND | O_RDWR, 777);
		free(heredoc_file);
	}
	while (42)
	{
		line = readline("herdoc> ");
		if (!line
			|| ft_memcmp(line, root->file, ft_strlen(root->file) + 1) == 0)
		{
			rl_on_new_line();
			break ;			
		}
		write(fd, line, ft_strlen(line));
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

char	*get_heredoc_file_name(t_data *data)
{
	static int	i;
	char		*path;
	char		*nbr;
	char		*heredoc_file;

	path = "/tmp/here_doc";
	nbr = ft_itoa(i);
	if (nbr == NULL)
		panic("Error ft_itoa\n", data);
	heredoc_file = ft_strjoin(path, nbr);
	if (heredoc_file == NULL)
	{
		free(nbr);
		panic("Error ft_strjoin\n", data);
	}
	free(nbr);
	i++;
	return (heredoc_file);
}
