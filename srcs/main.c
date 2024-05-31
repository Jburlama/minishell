/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:32:03 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/31 16:09:06 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	t_data	data;

	handle_signal();
	ft_memset(&data, 0, sizeof(data));
	while (42)
	{
		get_line();
		tokenize(&data);
		for (t_token *ptr = data.head; ptr; ptr = ptr->next)
			printf("content: %s | type %i\n", ptr->content, ptr->type);
		clear_list(&data.head);
	}
	free(rl_line_buffer);
}
