/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jburlama <Jburlama@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:54:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/05/26 20:55:25 by Jburlama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_signal(void)
{
	struct sigaction	sig_ign;
	struct sigaction	sig;

	sig_ign.sa_handler = SIG_IGN;
	sig.sa_handler = signal_handler;
	sigaction(SIGTERM, &sig_ign, NULL);
	sigaction(SIGQUIT, &sig_ign, NULL);
	sigaction(SIGINT, &sig, NULL);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}
