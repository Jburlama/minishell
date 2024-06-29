/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:26:55 by vbritto-          #+#    #+#             */
/*   Updated: 2024/06/25 14:39:13 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand(char *content, int i, int type)
{
	if ((content[i + 1] == '\0') || (content[i + 1] == ' ')
	|| (content[i + 1] == 34) || (content[i + 1] == 39))
	{
		if (content[0] == '$' && ft_strlen(content) == 1 && type == 1)
		{
			free(content);
			content = NULL;
		}
		return (0);
	}
	return (1);
}

int	check_content(t_token **tmp, t_token **keep, t_data *data)
{
	if (!(*tmp)->content)
	{
		if (*tmp == *keep)
		{
			if ((*tmp)->next)
				data->head = (*tmp)->next;
			else
			{
				data->head = NULL;
				return (0);
			}
			free(*tmp);
			*tmp = data->head;
		}
		else
		{
			if (!(*tmp)->next)
				(*keep)->next = NULL;
			else
				(*keep)->next = (*tmp)->next;
			free(*tmp);
			*tmp = *keep;
		}
	}
	return (1);
}

char	*get_env_name(char *content, char *exp,
	size_t *dol, t_data *data)
{
	char	*env_name;
	size_t	i;

	env_name = NULL;
	i = *dol - 1;
	while (ft_isalnum(content[*dol]))
	{
		(*dol)++;
	}
	env_name = ft_calloc(*dol - i, sizeof(char));
	if (!env_name)
		panic("calloc_fail", data);
	ft_strlcpy(env_name, content + i + 1, *dol - i);
	exp = getenv(env_name);
	free(env_name);
	return (exp);
}

char	*expand(char *content, t_data *data, size_t *dol, int type)
{
	char	*exp;
	char	*tmp;
	size_t	i;

	exp = NULL;
	i = *dol - 1;
	if(!check_expand(content, i, type))
		return (content);
	/*if ((content[i + 1] == '\0') || (content[i + 1] == ' ')
		|| (content[i + 1] == 34) || (content[i + 1] == 39))
		return (content);*/
	exp = get_env_name(content, exp, dol, data);
	if (!exp && (content[*dol]) == '\0')
	{
		free(content);
		return (NULL);
	}
	tmp = ft_calloc((ft_strlen(content) + ft_strlen(exp) - (*dol - i) + 1), sizeof(char));
	if (!tmp)
		panic("calloc_fail", data);
	ft_strlcpy(tmp, content, i + 1);
	if (exp)
		ft_strlcpy(tmp + i, exp, ft_strlen(exp) + 1);
	if (content[*dol] != '\0')
		ft_strlcpy(tmp + i + ft_strlen(exp), content + (*dol), ft_strlen(content) + 1 - (*dol));
	free(content);
	*dol = i;
	return (tmp);
}

void	prepare_dollar(t_data *data)
{
	size_t		dol;
	t_token		*tmp;
	t_token		*keep;

	tmp = data->head;
	keep = tmp;
	while (tmp)
	{
		dol = 0;
		while (tmp->content[dol])
		{
			if (tmp->content[dol] == '$' && tmp->type != SQUOTES)
			{
				dol++;
				tmp->content = expand(tmp->content, data, &dol, tmp->type);	
				if (tmp->content == NULL)
					dol = -1;
				if (!check_content(&tmp, &keep, data))
					return ;
			}
			dol++;
		}
		keep = tmp;
		tmp = tmp->next;
	}
}
