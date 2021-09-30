/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:52:21 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:52:36 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quots(t_mini *mini, int *i)
{
	*i = skip_beforeQ(mini, *i);
	if (!mini->cmd[*i])
	{
		ft_putstr_fd("minishell: unclosed quots\n", 2);
		mini->ff_exit = 2;
		return (1);
	}
	return (0);
}
