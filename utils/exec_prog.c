/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:17:24 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:48:23 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	changefd(t_commands *list, int num, t_mini *mini)
{
	if (list->fPipeIn)
		dup2(mini->dd[num][1], 1), close(mini->dd[num][0]);
	if (list->redirFlag == 1 || list->redirFlag == 2)
		dup2(list->fdOut, 1);
	if (list->fPipeOut)
		dup2(mini->dd[num - 1][0], 0), close(mini->dd[num - 1][0]);
	if (list->redirFlag == 3)
		dup2(list->fdOut, 0);
	else if (list->redirFlag == 4)
		dup2(list->pipe_heredoc[0], 0), close(list->pipe_heredoc[1]);
}

static void	exec_main(t_commands *list, t_mini *mini, int num)
{
	char	**env;
	int		i;

	i = 0;
	mini->tmpEnv = mini->envList;
	while (mini->tmpEnv && ++i)
	{
		if (!ft_strcmp(mini->tmpEnv->name, "SHLVL"))
			--i;
		mini->tmpEnv = mini->tmpEnv->next;
	}
	env = malloc(sizeof(char *) * (i + 2));
	mini->tmpEnv = mini->envList;
	i = 0;
	while (mini->tmpEnv)
	{
		if (mini->tmpEnv->vision)
			env[i++] = ft_strdup(mini->tmpEnv->full);
		mini->tmpEnv = mini->tmpEnv->next;
	}
	env[i] = NULL, shlvl_edit(env), changefd(list, num, mini);
	execve(list->full_cmd[0], list->full_cmd, env), i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

static void	execution(t_commands *list, t_mini *mini, int num, char *tmp)
{
	int	id;

	id = fork(), signal(SIGQUIT, SIG_IGN);
	if (!id)
	{
		exec_main(list, mini, num), ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(": ", 2), ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), free(tmp);
		exit(126);
	}
	else
	{
		if (list->fPipeIn)
			close(mini->dd[num][1]);
		if (list->fPipeOut)
			close(mini->dd[num - 1][0]);
		waitpid(id, &mini->ff_exit, WUNTRACED);
	}
	sig_main();
}

static int	checkstat(t_commands *list, t_mini *mini, char *tmp, int flag)
{
	if (flag)
	{
		write(2, "minishell: ", 11), write(2, tmp, ft_strlen(tmp));
		write(2, ": No such file or directory\n", 28);
		free(list->full_cmd[0]), list->full_cmd[0] = tmp;
		mini->ff_exit = 127;
		return (0);
	}
	free(tmp);
	return (1);
}

int	exec_prog(t_commands *list, t_mini *mini, int num)
{
	struct stat	buf;
	int			flag;
	char		*tmp;
	int			i;

	flag = 0;
	tmp = ft_strdup(list->full_cmd[0]);
	if (!ft_strncmp(list->full_cmd[0], "./", 2))
		edit_first(list, &flag);
	i = 0;
	while (list->full_cmd[0][i] && list->full_cmd[0][i] != '/')
		++i;
	if (stat(list->full_cmd[0], &buf) == -1 || !list->full_cmd[0][i])
		return (checkstat(list, mini, tmp, flag));
	if (open(list->full_cmd[0], O_DIRECTORY) != -1)
	{
		write(2, "minishell: ", 11), write(2, tmp, ft_strlen(tmp));
		write(2, ": is a directory\n", 17), mini->ff_exit = 126;
		free(list->full_cmd[0]), list->full_cmd[0] = tmp;
		return (0);
	}
	else
		execution(list, mini, num, tmp);
	free(tmp), mini->lastCMD = 0;
	return (0);
}
