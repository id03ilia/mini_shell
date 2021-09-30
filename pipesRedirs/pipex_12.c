/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:35:32 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/29 13:22:25 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_cmd(char *path_i, char *cmd)
{
	char	*t;
	char	*path_with_cmd;

	t = ft_strjoin(path_i, "/");
	path_with_cmd = ft_strjoin(t, cmd);
	free(t);
	return (path_with_cmd);
}

static void	close_dup(t_mini *piped, t_commands *tmp, int s)
{
	if (tmp->fPipeIn == 1)
	{
		close(piped->dd[s][0]);
		dup2(piped->dd[s][1], 1);
	}
	if (tmp->fPipeOut == 1)
	{
		close(piped->dd[s - 1][1]);
		dup2(piped->dd[s - 1][0], 0);
	}
	if (tmp->fdOut)
		dup2(tmp->fdOut, 1);
	if (tmp->fdIn)
		dup2(tmp->fdIn, 0);
	if (tmp->check_heredoc)
		dup2(tmp->pipe_heredoc[0], 0);
}

static char	**search_PATH(t_mini *piped)
{
	char	**paths;

	while (piped->envList)
	{
		if (ft_strncmp(piped->envList->name, "PATH", 4) == 0)
		{
			piped->env = malloc(sizeof(char *) * 2);
			piped->env[0] = piped->envList->name;
			piped->env[1] = NULL;
			paths = ft_split(piped->envList->full + 5, ':');
			return (paths);
		}
		else
			piped->envList = piped->envList->next;
	}
	write(2, "PATH not found in our env", 25);
	exit(1);
}

void	pipex_all(t_mini *piped, t_commands *tmp, int s)
{
	char	**paths;
	int		i;
	char	*path_w;

	close_dup(piped, tmp, s);
	paths = search_PATH(piped);
	i = 0;
	while (paths[i])
	{
		path_w = join_cmd(paths[i], tmp->full_cmd[0]);
		execve(path_w, (char *const *)tmp->full_cmd, piped->env);
		free(path_w);
		i++;
	}
	free_mass(piped->env);
	free_mass(paths);
	write(2, "Command not found: ", 19);
	write(2, tmp->full_cmd[0], ft_strlen(tmp->full_cmd[0]));
	write(2, "\n", 1);
	exit (127);
}

int	cmd_exec(t_commands *tmp, t_mini *mini, int s)
{	
	mini->pid = fork();
	if (mini->pid < 0)
		std_error(1, strerror(errno), tmp->full_cmd[0]);
	if (mini->pid == 0)
		pipex_all(mini, tmp, s);
	mini->lastCMD = 0;
	return (0);
}
