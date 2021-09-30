/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:45:26 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:59:50 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_listener(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, sig_listener);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sig_quit(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
	g_ff_exit = 131;
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_cltr_c_HD(int sig)
{
	(void)sig;
	write(2, "\b\b  \b\b", 6);
	exit(1);
}
