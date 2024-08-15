/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dollar_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:03:41 by vbritto-          #+#    #+#             */
/*   Updated: 2024/08/15 17:32:03 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit(char *tmp, char *content, t_data *data)
{
	int		i;
	char	*tmp_exit;

	tmp_exit = NULL;
	i = 0;
	while (content[i] && content[i + 1])
	{
		if (content[i] == '$' && content[i + 1] == '?')
		{
			tmp_exit = ft_itoa(data->print_exit_code);
			tmp = ft_strdup(tmp_exit);
			free (tmp_exit);
		}
		i++;
	}
	return (tmp);
}

char	*dollar_number(char *content, char *tmp, t_data *data, size_t *dol)
{
	int		i;

	i = (*dol);
	while (ft_isalnum(content[*dol]))
		(*dol)++;
	if (content[i] == 48)
	{
		if (content[i + 1] == '\0')
			tmp = ft_strdup("./minishell\0");
		else
			tmp = ft_strjoin("./minishell\0", (content + (i) + 1));
	}
	else if ((content[i] > 48 && content[i] <= 57))
	{
		if (content[i + 1] != '\0')
		{
			tmp = ft_strdup(content + i + 1);
			(*dol)--;
		}
		else
			(*dol) = 0;
	}
	if (tmp == NULL)
		tmp = expand_exit(tmp, content, data);
	return (tmp);
}

char	*expand_number(char *c, t_data *data, size_t *d)
{
	char	*e;
	char	*tp;
	size_t	i;

	e = NULL;
	i = *d - 1;
	e = dollar_number(c, e, data, d);
	if (e == NULL)
	{
		free(c);
		return (NULL);
	}
	tp = ft_calloc((ft_strlen(c) + ft_strlen(e) - (*d - i) + 1), sizeof(char));
	if (!tp)
		panic("calloc_fail", data);
	ft_strlcpy(tp, c, i + 1);
	if (e)
		ft_strlcpy(tp + i, e, ft_strlen(e) + 1);
	free(c);
	if (e && e[*d - 1] == '$')
		*d = -1;
	else
		*d = i;
	free (e);
	return (tp);
}

int	check_expand(char *content, int i, int type, size_t *dol)
{
	if ((((content)[i + 1] == '\0') || ((content)[i + 1] == ' ')
		|| ((content)[i + 1] == 34) || ((content)[i + 1] == 39))
		|| ((content)[0] == '$' && ft_strlen(content) == 1 && type == 1)
		|| ((content)[0] == '$' && content[1] && content[1] == '$')
		)
	{
		(*dol)--;
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
