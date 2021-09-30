/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:02:28 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:02:31 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkslash(t_mini *mini, int i, int check)
{
	int	count;

	count = 0;
	if (mini->cmd[i] == '\'' && check)
	{
		mini->quot = 0;
		return (1);
	}
	while (mini->cmd[--i] == '\\' && i >= 0)
		++count;
	if (count % 2)
		return (0);
	mini->quot = 0;
	return (1);
}

int	check_stop(char check)
{
	if (check == '|' || check == '>' || check == '<')
		return (1);
	return (0);
}

static char	*before_f1(t_mini *mini, int *i)
{
	char	*before;

	if (mini->cmd[*i + 1] == mini->cmd[*i])
	{
		before = ft_substr(mini->cmd, 0, *i + 3);
		before[*i] = ' ';
		before[*i + 1] = mini->cmd[*i];
		before[*i + 2] = mini->cmd[*i];
		++(*i);
	}	
	else
	{
		before = ft_substr(mini->cmd, 0, *i + 2);
		before[*i] = ' ';
		before[*i + 1] = mini->cmd[*i];
	}
	return (before);
}

static char	*before_f2(t_mini *mini, int *i)
{
	char	*before;

	if (mini->cmd[*i + 1] == mini->cmd[*i])
	{
		before = ft_substr(mini->cmd, 0, *i + 2);
		++(*i);
	}
	else
		before = ft_substr(mini->cmd, 0, *i + 1);
	return (before);
}

char	*before_f(t_mini *mini, int *i)
{
	char	*before;
	int		t;

	t = *i;
	if (mini->cmd[*i] == '>' || mini->cmd[*i] == '<')
	{
		if (*i && mini->cmd[*i - 1] != ' ')
			before = before_f1(mini, i);
		else
			before = before_f2(mini, i);
		++(*i);
	}
	else if (*i && mini->cmd[*i - 1] != ' ')
	{
		before = ft_substr(mini->cmd, 0, (*i + 2));
		before[t] = ' ';
		before[t + 1] = mini->cmd[t];
		++(*i);
	}
	else
		before = ft_substr(mini->cmd, 0, *i + 1);
	return (before);
}
