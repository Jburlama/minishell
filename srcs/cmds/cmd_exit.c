/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:10:57 by vbritto-          #+#    #+#             */
/*   Updated: 2024/07/20 19:21:12 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit_number(char *number, int *i)
{
	while (number[*i])
	{
		if (!ft_isdigit(number[*i])
			|| (ft_atol(number) < INT_MIN || ft_atol(number) > INT_MAX))
		{
			ft_printf("minishell: exit: %s: numeric argumnet required\n",
				number);
			return (2);
		}
		(*i)++;
	}
	(*i) = ft_atol(number);
	if (number[0] == '-')
	{
		while ((*i) < 0)
			(*i) += 256;
	}
	else
	{
		while ((*i) > 256)
			(*i) %= 256;
	}
	return ((*i));
}

int	len_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	free_exit(t_data *data)
{
	free(rl_line_buffer);
	clear_tree(data->root);
	clear_args(data->env);
	clear_args(data->export);
	return (data->exit_code);
}

void	many_args(t_data *data, t_exec *node)
{
	int	i;

	i = 0;
	while (node->args[1][i])
	{
		if (!ft_isdigit(node->args[1][i]))
		{
			ft_printf("minishell: exit: %s: numeric argumnet required\n",
				node->args[1]);
			free_exit(data);
			exit (1);
		}
		i++;
	}
	data->exit_code = 1;
	ft_printf("exit: too many arguments\n");
}

int	cmd_exit(t_data	*data, t_exec *node)
{
	int	i;
	int	exit_number;

	data->exit_code = 0;
	i = len_args(node->args);
	ft_printf("exit\n");
	if (i > 2)
	{
		many_args(data, node);
		return (1);
	}
	else if (node->args[1])
	{
		if (node->args[1][0] == '\0')
		{
			ft_printf("minishell: exit: : numeric argumnet required\n");
			return (2);
		}
		i = 0;
		if (node->args[1][0] == '+' || node->args[1][0] == '-')
			i++;
		data->exit_code = ft_exit_number(node->args[1], &i);
	}
	exit_number = free_exit(data);
	exit(exit_number);
}
