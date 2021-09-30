/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:03:55 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:21:24 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	args_num2(t_mini *mini, int *i, int count)
{
	int	symb;

	symb = *i;
	while (symb >= 0 && mini->cmd[symb] == ' ')
		--symb;
	if (symb >= 0)
	{
		while (mini->cmd[*i] == ' ' && mini->cmd[*i])
			++(*i);
		if (mini->cmd[*i])
		{
			--(*i);
			++count;
		}
	}
	return (count);
}

void	args_num(t_mini *mini)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i] == '\"' || mini->cmd[i] == '\'')
			i = skip_beforeQ(mini, i);
		else if (mini->cmd[i] == ' ')
			count = args_num2(mini, &i, count);
		if (mini->cmd[i])
			++i;
	}
	mini->args = count + 1;
}
