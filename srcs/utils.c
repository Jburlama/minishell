/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:18:02 by Jburlama          #+#    #+#             */
/*   Updated: 2024/06/12 17:31:33 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	save_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("Error calling fork", data);
	return (pid);
}

bool	is_all_white(char	*str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (is_white_space(str && str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	jump_white_spaces(int *i)
{
	if (rl_line_buffer[(*i) + 1]
		&& is_white_space(rl_line_buffer[(*i) + 1]))
	{
		while (rl_line_buffer[(*i) + 1]
			&& is_white_space(rl_line_buffer[(*i) + 1]))
			(*i)++;
	}
}

bool	is_special(char c)
{
	char	*special;
	int		i;

	special = "|<>()&";
	i = 0;
	while (special[i])
	{
		if (c == special[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (true);
	else
		return (false);
}
