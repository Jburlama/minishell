/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:54 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/09 21:52:32 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	create_tree(t_data *data)
{
	t_token	*tokens_ptr;

	tokens_ptr = data->head;
	data->root = parse_exec(&tokens_ptr);
	if (data->root == NULL)
		panic("error calling parse_exec", data);
}

void	*parse_exec(t_token **tokens)
{
	t_exec	*exec;
	void	*root;
	char	*str;

	exec = ft_calloc(sizeof(*exec), 1);
	if (exec == NULL)
		return (NULL);
	exec->type = EXEC;
	root = exec;
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		root = parse_redir(root, tokens);
		if (!exec->args)
			str = ft_strjoin("", (*tokens)->content);
		else
		{
			str = ft_strjoin(exec->args, (*tokens)->content);
			free(exec->args);
		}
		if (str == NULL)
			return (NULL);
		exec->args = str;
		(*tokens) = (*tokens)->next;
	}
	return (root);
}

void	*parse_redir(void *root, t_token **tokens)
{
	t_redir	*ret;

	if ((*tokens) && (*tokens)->type != SPECIAL)
		return (root);
	ret = ft_calloc(sizeof(t_redir), 1);
	if (ret == NULL)
		return (NULL);
	ret->type = REDIR;
	ret->file_type = (*tokens)->type;
	(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type == WHITE_SPACE)
		(*tokens) = (*tokens)->next;
	ret->file = ft_strdup((*tokens)->content);
	if (ret->file == NULL)
		return (NULL);
	ret->down = root;
	if (!(*tokens)->next)
		return (ret);
	(*tokens) = (*tokens)->next;
	return (parse_redir(ret, tokens));
}
