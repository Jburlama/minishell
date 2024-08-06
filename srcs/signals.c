/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbritto- <vbritto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:54:06 by Jburlama          #+#    #+#             */
/*   Updated: 2024/07/31 18:59:46 by vbritto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status_exit;

void	handle_signal(void)
{
	struct sigaction	sig_ign;
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	ft_memset(&sig_ign, 0, sizeof(sig_ign));
	sig_ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_ign, NULL);
	sig.sa_handler = signal_handler;
	sigaction(SIGINT, &sig, NULL);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status_exit = SIGINT;
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	update_signals(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
}

void	default_sig(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
}
