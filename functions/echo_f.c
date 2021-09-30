/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:00:12 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 11:20:39 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo2(t_commands *list, int *i, int *flag, int tmp)
{
	int	j;

	while (list->full_cmd[*i] && list->full_cmd[*i][0] == '-'
		&& list->full_cmd[*i][1] == 'n')
	{
		j = 1;
		while (list->full_cmd[*i][j] && list->full_cmd[*i][j] == 'n')
			++j;
		if (!list->full_cmd[*i][j])
		{
			*flag = 1;
			++(*i);
		}
		else
			break ;
	}
	while (list->full_cmd[*i])
	{
		ft_putstr_fd(list->full_cmd[*i], tmp);
		if (list->full_cmd[++(*i)])
			write(tmp, " ", 1);
	}
}

void	echo_f(t_commands *list, int num, t_mini *mini)
{
	int	i;
	int	tmp;
	int	flag;

	i = 1;
	flag = 0;
	tmp = 1;
	if (list->fPipeIn && !list->redirFlag)
		tmp = mini->dd[num][1];
	if (list->redirFlag)
		tmp = list->fdOut;
	echo2(list, &i, &flag, tmp);
	if (i - flag == 1)
		write(tmp, "", 0);
	if (!flag)
		write(tmp, "\n", 1);
	mini->ff_exit = 0;
}
