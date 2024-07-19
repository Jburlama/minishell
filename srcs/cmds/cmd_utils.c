/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:26:46 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/19 09:35:14 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sin;
	long	res;

	i = 0;
	sin = 1;
	res = 0;
	if (str[i] == 45)
	{
		sin *= -1;
		i++;
	}
	while (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] != '\0') && (str[i] >= 48 && str[i] <= 57))
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sin);
}

void	change_export(char **export, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(export[i]);
	free(export[i]);
	export[i] = ft_strdup(export[j]);
	free(export[j]);
	export[j] = ft_strdup(tmp);
	free (tmp);
}

void	sort_export(char **export, int n)
{
	int	j;
	int	z;
	int	i;

	i = 0;
	while (i < n)
	{
		j = i;
		while (j < n)
		{
			z = 0;
			while (export[i][z] && export[j][z]
					&& (export[i][z] == export[j][z]))
				z++;
			if (export[i][z] < export[j][z])
				change_export(export, i, j);
			j++;
		}
		i++;
	}
}

int	just_export(t_data *data, t_exec *node)
{
	int	i;

	i = 0;
	if (node->args[1] == NULL)
	{
		while (data->export[i])
			i++;
		sort_export(data->export, i);
		i--;
		while (i >= 0)
		{
			ft_printf("declare -x %s\n", data->export[i]);
			i--;
		}
		return (1);
	}
	else
		return (0);
}

int	is_export(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == ' ') || c == '+')
		return (8);
	else
		return (0);
}
