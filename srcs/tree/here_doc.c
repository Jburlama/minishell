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

void	here_doc(t_redir *root)
{
	int		fd_out;
	char	*line;
	int		fd;
	char	*file_name;

	file_name = open_heredoc_for_write(&fd);
	fd_out = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDIN_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	here_doc_sig();
	while (42)
	{
		line = readline("heredoc> ");
		if (!line
			|| ft_memcmp(line, root->file, ft_strlen(root->file) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	default_sig();
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
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

void	here_doc_sig(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}
