/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:36:00 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/30 11:33:41 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_signal_pipe(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	g_ff_exit = 130;
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_cmd(void)
{
	signal(SIGINT, ft_signal_pipe);
	signal(SIGQUIT, ft_sig_quit);
}

void	ft_signal_pipe_HD(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

void	ft_signal_hd(void)
{
	signal(SIGQUIT, ft_signal_pipe_HD);
	signal(SIGINT, ft_signal_cltr_c_HD);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_cltr_c_2(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	g_ff_exit = -101;
}
