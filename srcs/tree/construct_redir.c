/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:30:27 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/20 18:15:50 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*construct_redir(void	*root, t_token **tokens, t_data *data)
{
	t_redir	*ptr;
	t_redir	*new;

	new = redir_alloc(tokens, data);
	if (((t_exec *)root)->type == EXEC)
	{
		new->down = root;
		return (new);
	}
	ptr = root;
	while (((t_exec *)ptr->down)->type != EXEC)
		ptr = ptr->down;
	new->down = ptr->down;
	ptr->down = new;
	return (root);
}

t_redir	*redir_alloc(t_token **tokens, t_data *data)
{
	t_redir	*new;

	new = ft_calloc(sizeof(*new), 1);
	if (new == NULL)
		return (NULL);
	new->type = REDIR;
	new->file_type = (*tokens)->type;
	if ((*tokens)->type == DQUOTES || (*tokens)->type == SQUOTES)
	{
		new->quote_type = (*tokens)->type;
		new->file_type = (*tokens)->file;
	}
	if (new->file_type == HERE_DOC)
		new->file = here_doc(new, (*tokens)->content, data);
	else
		new->file = ft_strdup((*tokens)->content);
	return (new);
}
