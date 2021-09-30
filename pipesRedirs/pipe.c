/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:35:22 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/29 11:52:36 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_init(t_mini *mini, t_commands *tmp)
{
	int	count_cmd;

	count_cmd = 0;
	tmp = mini->always1st;
	while (tmp)
	{
		count_cmd++;
		tmp = tmp->next;
	}
	mini->count_cmd = count_cmd;
	return (mini->count_cmd);
}

void	pipe_use(t_mini *mini, t_commands *tmp)
{
	int	count_cmd;
	int	cc;

	count_cmd = pipe_init(mini, tmp);
	mini->dd = malloc(sizeof(int *) * (count_cmd - 1));
	if (!mini->dd)
	{
		ft_putstr_fd("Malloc error. Exiting..", 2);
		exit (-10);
	}
	cc = 0;
	while (cc < (count_cmd - 1))
	{
		mini->dd[cc] = malloc(sizeof(int) * 2);
		if (!mini->dd[cc])
		{
			ft_putstr_fd("Malloc error. Exiting..", 2);
			exit (-10);
		}
		if (pipe(mini->dd[cc++]) == -1)
		{
			ft_putstr_fd("Pipe opening error. Exiting..", 2);
			exit (-10);
		}
	}
}
