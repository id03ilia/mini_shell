/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:04:19 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:52:12 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_pipe(t_mini *mini, int *i)
{
	int	tmp;

	tmp = (*i)++ - 1;
	while (tmp >= 0 && mini->cmd[tmp] == ' ')
		--tmp;
	if (tmp == -1)
	{
		mini->ff_exit = 2;
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (mini->cmd[*i] && mini->cmd[*i] == ' ')
		++(*i);
	if (!mini->cmd[*i])
	{
		mini->ff_exit = 2, ft_putstr_fd("minishell: unclosed pipe\n", 2);
		return (1);
	}
	if (mini->cmd[*i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(&mini->cmd[*i], 2), write(2, "\'\n", 2), mini->ff_exit = 2;
		return (1);
	}
	return (0);
}

static void	printsynt(t_mini *mini, int *i)
{
	if (mini->cmd[*i + 1] == mini->cmd[*i])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &mini->cmd[*i], 1), write(2, &mini->cmd[*i + 1], 1);
		write(2, "\'\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &mini->cmd[*i], 1), write(2, "\'\n", 2);
	}
	mini->ff_exit = 2;
	mini->fakeHD = 1;
}

static int	check_redirects(t_mini *mini, int *i)
{
	int	tmp;

	if (mini->cmd[*i] == mini->cmd[*i + 1])
		++(*i);
	tmp = *i;
	++(*i);
	while (mini->cmd[(*i)] == ' ')
		++(*i);
	if (mini->cmd[*i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|\'\n", 2);
		mini->ff_exit = 2;
		mini->fakeHD = 1;
		return (0);
	}
	if (mini->cmd[*i] == '>' || mini->cmd[*i] == '<')
	{
		printsynt(mini, i);
		return (0);
	}
	*i -= 1;
	return (0);
}

static int	pipe_redir(t_mini *mini, int i)
{
	if (mini->cmd[i] == '|')
	{
		if (check_pipe(mini, &i))
		{
			mini->ff_exit = 2;
			return (-1);
		}
	}
	else if (mini->cmd[i] == '>' || mini->cmd[i] == '<')
	{
		if (check_redirects(mini, &i))
		{
			mini->ff_exit = 2;
			return (-1);
		}
	}
	return (i);
}

int	checkstr(t_mini *mini)
{
	int		i;

	i = 0;
	mini->fakeHD = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i] == '\'' || mini->cmd[i] == '\"')
		{
			if (check_quots(mini, &i))
				return (0);
		}
		i = pipe_redir(mini, i);
		if (i == -1)
			return (0);
		if (mini->cmd[i])
			++i;
	}
	return (1);
}
