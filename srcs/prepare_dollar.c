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

char	*get_my_env(t_data *data, char *env_name)
{
	int		i;
	int		j;
	char	*exp;

	i = 0;
	j = 0;
	exp = NULL;
	while (data->env[j])
	{
		i = 0;
		while (data->env[j][i])
		{
			if (data->env[j][i] == '=')
				break ;
			i++;
		}
		if (i == (int)ft_strlen(env_name))
		{
			if (ft_memcmp(data->env[j], env_name, i) == 0)
				exp = ft_strdup(data->env[j] + i + 1);
		}
		j++;
	}
	return (exp);
}

char	*get_env_name(char *content, char *exp,
	size_t *dol, t_data *data)
{
	char	*env_name;
	size_t	i;

	env_name = NULL;
	i = *dol - 1;
	while (ft_isalnum(content[*dol]))
		(*dol)++;
	env_name = ft_calloc(*dol - i, sizeof(char));
	if (!env_name)
		panic("calloc_fail", data);
	ft_strlcpy(env_name, content + i + 1, *dol - i);
	exp = get_my_env(data, env_name);
	free(env_name);
	return (exp);
}

// c = content
// d = dol
// e = exp

char	*expand(char *c, t_data *data, size_t *d, int type)
{
	char	*e;
	char	*tp;
	size_t	i;

	e = NULL;
	i = *d - 1;
	if (!check_expand(c, i, type, d))
		return (c);
	e = get_env_name(c, e, d, data);
	if (!e && (c[*d]) == '\0')
		return (free(c), NULL);
	tp = ft_calloc((ft_strlen(c) + ft_strlen(e) - (*d - i) + 1), sizeof(char));
	if (!tp)
		panic("calloc_fail", data);
	ft_strlcpy(tp, c, i + 1);
	if (e)
		ft_strlcpy(tp + i, e, ft_strlen(e) + 1);
	if (c[*d] != '\0')
		ft_strlcpy(tp + i + ft_strlen(e), c + (*d), ft_strlen(c) + 1 - (*d));
	free(c);
	free(e);
	*d = i - 1;
	return (tp);
}

void	second_prepare_dollar(t_data *data)
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
		while (tmp->content[dol] && tmp->content[dol + 1])
		{
			if (((tmp->content[dol] == '$' && tmp->type != 4))
				&& (ft_isexp(tmp->content[dol + 1])))
			{
				dol++;
				tmp->content = expand_number(tmp->content, data, &dol);
				if (!check_content(&tmp, &keep, data))
					return ;
			}
			dol++;
		}
		keep = tmp;
		tmp = tmp->next;
	}
	second_prepare_dollar(data);
}
