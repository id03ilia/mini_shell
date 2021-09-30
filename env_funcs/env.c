/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:36:38 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 09:22:43 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_f(t_commands *list, int num, t_mini *mini)
{
	t_env	*temp;
	int		tmp;

	tmp = 1;
	if (list->fPipeIn)
		tmp = mini->dd[num][1];
	if (list->redirFlag)
		tmp = list->fdOut;
	temp = mini->envList;
	while (temp)
	{
		if (temp->vision && ft_strchr(temp->full, '='))
		{
			ft_putstr_fd(temp->full, tmp);
			write(tmp, "\n", 1);
		}
		temp = temp->next;
	}
	mini->ff_exit = 0;
}
