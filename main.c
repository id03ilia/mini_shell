/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:15:00 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/30 11:37:58 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mass_free(t_mini *mini, int num)
{
	t_commands	*tmp;
	t_commands	*tmp2;
	int			i;

	tmp = mini->always1st;
	tmp2 = tmp;
	if (tmp->check_heredoc)
		free (tmp->stopWord);
	while (tmp)
	{
		i = 0;
		while (tmp->full_cmd[i] != NULL)
			free(tmp->full_cmd[i++]);
		free(tmp->full_cmd);
		tmp = tmp->next;
		free(tmp2);
		tmp2 = tmp;
	}
	free(mini->cmd);
	if (num && mini->dd)
		free_mass_int_pipe(mini->dd, mini->count_cmd - 1);
}

static void	executing_cmds(t_commands *tmp, t_mini *mini, int num)
{
	while (tmp)
	{
		ft_signal_cmd();
		if (isItBuildin(tmp, num, mini))
			num += 0;
		else
			if (exec_prog(tmp, mini, num))
				cmd_exec(tmp, mini, num);
		if (tmp->fPipeOut == 0 && tmp->fPipeIn == 1)
			close(mini->dd[num][1]);
		if (tmp->fPipeIn == 1 && tmp->fPipeOut == 1)
			close(mini->dd[num - 1][0]), close(mini->dd[num][1]);
		if (tmp->fPipeIn == 0 && tmp->fPipeOut == 1)
			close(mini->dd[num - 1][0]), close(mini->dd[num - 1][1]);
		if (tmp->check_heredoc)
			close(tmp->pipe_heredoc[0]);
		++num;
		tmp = tmp->next;
	}
	if (!mini->lastCMD)
		waitpid(mini->pid, &mini->ff_exit, 0);
	if (g_ff_exit == 131 || g_ff_exit == 130)
		mini->ff_exit = g_ff_exit;
	if (mini->ff_exit > 255)
		mini->ff_exit /= 256;
}

static void	start_cmd(t_mini *mini)
{
	sig_main();
	g_ff_exit = 0;
	rl_outstream = stderr;
	mini->lastCMD = 0;
	mini->cmd = readline("minishell: ");
	if (!mini->cmd)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}

static void	parsing(t_mini *mini)
{
	t_commands	*tmp;

	preparser(mini);
	args_num(mini);
	cut_cmd(mini);
	tmp = mini->always1st;
	while (tmp)
	{
		tmp->check_heredoc = 0;
		if (isHeredoc(tmp, mini))
			redirect_f(tmp, mini, tmp->stopWord);
		if (check_redir(tmp, mini))
			break ;
		if (redir_edit(tmp, mini))
		{
			mini->fakeHD = 1;
			mini->ff_exit = 1;
			break ;
		}
		parser(tmp, mini);
		tmp = tmp->next;
	}
	if (g_ff_exit == -101)
		mini->ff_exit = 1;
}

int	main(int argc, char **argv, char **env)
{
	t_mini		mini;

	init(&mini, env, argv, argc);
	while (1)
	{
		start_cmd(&mini);
		if (mini.cmd[0])
			add_history(mini.cmd), history_wr(mini.cmd, mini.fdH);
		if (!checkstr(&mini))
		{
			free(mini.cmd);
			continue ;
		}
		parsing(&mini);
		if (mini.fakeHD || g_ff_exit)
		{
			mass_free(&mini, 0);
			continue ;
		}
		pipe_use(&mini, mini.always1st);
		executing_cmds(mini.always1st, &mini, 0);
		mass_free(&mini, 1);
	}
}
