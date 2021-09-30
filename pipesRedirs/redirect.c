/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:35:40 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/29 14:41:33 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_child(t_commands *list, char *stop)
{
	char	*line;

	ft_signal_hd();
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (ft_strcmp(line, stop) == 0)
		{
			free(stop);
			break ;
		}
		write(list->pipe_heredoc[1], line, ft_strlen(line));
		write(list->pipe_heredoc[1], "\n", 1);
	}
	free(line);
	close(list->pipe_heredoc[1]);
	exit(1);
}

void	redirect_parent(t_commands *list, t_mini *mini, pid_t pid1)
{
	int	he;

	g_ff_exit = 0;
	signal(SIGINT, ft_signal_cltr_c_2);
	close(list->pipe_heredoc[1]);
	waitpid(pid1, &he, WUNTRACED);
	sig_main();
	if (he / 256 == 5)
	{
		list->fRedir = 0;
		write(1, "\n", 1);
		mini->count_cmd = 0;
	}
}

void	redirect_f(t_commands *list, t_mini *mini, char *stop)
{
	pid_t	pid1;

	list->check_heredoc = 1;
	if (pipe(list->pipe_heredoc) == -1)
	{
		write(2, "Error pipe_here_doc", 19);
		exit(-1);
	}
	pid1 = fork();
	if (pid1 == 0)
		redirect_child(list, stop);
	else
		redirect_parent(list, mini, pid1);
}
