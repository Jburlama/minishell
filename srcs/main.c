/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:32:03 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/26 17:32:14 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int main(void)
{
	while (42)
	{
		get_line();
	}
}

void	get_line()
{
	free(readline(GREEN "Minishell: " RESET));
	if (ft_memcmp(rl_line_buffer, "exit\0", 5) == 0)
	{
		free(rl_line_buffer);
		exit(0);
	}
}
