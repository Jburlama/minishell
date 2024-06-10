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

	exec = ft_calloc(sizeof(*exec), 1);
	if (exec == NULL)
		return (NULL);
	exec->type = EXEC;
	root = exec;
	while ((*tokens))
	{
		root = parse_redir(root, tokens);
		if (!(*tokens))
			break ;
		if (t_exec_fill(&exec, *tokens) == NULL)
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	return (root);
}

void	*parse_redir(void *root, t_token **tokens)
{
	void	*ret;

	ret = root;
	while ((*tokens) && ((*tokens)->type == SPECIAL))
	{
		(*tokens) = (*tokens)->next;
		if (*tokens)
			ret = construct_redir(ret, tokens);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

void	*construct_redir(void	*subnode, t_token **tokens)
{
	t_redir	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (ret == NULL)
		return (NULL);
	ret->type = REDIR;
	ret->file_type = (*tokens)->type;
	ret->file = ft_strdup((*tokens)->content);
	if (ret->file == NULL)
		return (NULL);
	ret->down = subnode;
	(*tokens) = (*tokens)->next;
	return (ret);
}

t_exec	*t_exec_fill(t_exec **exec, t_token *token)
{
	char	*str;

	if (!(*exec)->args)
		str = ft_strdup(token->content);
	else
	{
		str = ft_strjoin((*exec)->args, token->content);
		free((*exec)->args);
	}
	(*exec)->args = str;
	if ((*exec)->args == NULL)
		return (NULL);
	return (*exec);
}

