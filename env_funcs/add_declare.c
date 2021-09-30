/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_declare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:56:20 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:31:00 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_wop_declare(t_mini *mini, t_commands *list, int num)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (list->fPipeIn)
		j = mini->dd[num][1];
	if (list->redirFlag)
		j = list->fdOut;
	while (mini->env_exp[i])
	{
		ft_putstr_fd(mini->declare, j);
		ft_putstr_fd(mini->env_exp[i], j);
		write(j, "\n", 1);
		free(mini->env_exp[i++]);
	}
	free(mini->env_exp);
}
