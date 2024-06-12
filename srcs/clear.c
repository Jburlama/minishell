/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:37 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 22:13:06 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_list(t_token	**head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		*head = (*head)->next;
		free(temp->content);
		free(temp);
		temp = *head;
	}
	*head = NULL;
}

void	clear_tree(void	*root)
{
	int	i;

	if (root == NULL)
		return ;
	else if (((t_exec *)root)->type == EXEC)
	{
		i = 0;
		if (((t_exec *)root)->args)
			clear_args(((t_exec *)root)->args);
		free(root);
		return ;
	}
	else if (((t_redir *)root)->type == REDIR)
	{
		if (((t_redir *)root)->file)
			free(((t_redir *)root)->file);
		clear_tree(((t_redir *)root)->down);
		free(root);
	}
	else if (((t_pipe *)root)->type == PIPE)
	{
		clear_tree(((t_pipe *)root)->left);
		clear_tree(((t_pipe *)root)->right);
		free(root);
	}
}

void	clear_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
