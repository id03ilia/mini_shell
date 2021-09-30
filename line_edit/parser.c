/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:15:17 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:00:40 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*after_f(t_mini *mini, int *i)
{
	char	*after;

	if (mini->cmd[*i] != ' ')
	{
		--(*i);
		after = ft_strdup(mini->cmd + *i);
		after[0] = ' ';
		*i += 1;
	}
	else
		after = ft_strdup(mini->cmd + *i);
	return (after);
}

char	*add_spaces(t_mini *mini, int *i)
{
	char	*before;
	char	*after;
	int		t;

	t = *i;
	after = NULL;
	before = before_f(mini, i);
	if (mini->cmd[t] == '|' || mini->cmd[t] == ';')
	{
		after = ft_strdup(mini->cmd + t + 1);
		if (after[0] != ' ')
		{
			before = strjoin_free(before, " ");
			++(*i);
		}
	}
	else if (mini->cmd[t] == '>' || mini->cmd[t] == '<')
		after = after_f(mini, i);
	before = strjoin_free(before, after);
	free(after);
	free(mini->cmd);
	return (before);
}

int	preparser(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i] == '\"' || mini->cmd[i] == '\'')
		{
			if (checkslash(mini, i, 0))
			{
				i = skip_beforeQ(mini, i);
				if (!mini->cmd[i] && mini->quot)
					return (1);
			}
		}
		if (check_stop(mini->cmd[i]))
			mini->cmd = add_spaces(mini, &i);
		if (mini->cmd[i])
			++i;
	}
	return (0);
}

static int	parser2(t_commands *list, t_mini *mini, int i, int l)
{
	if (list->full_cmd[l][i] == '\\')
		list->full_cmd[l] = ft_slash(list->full_cmd[l], &i);
	else if (list->full_cmd[l][i] == '$')
		list->full_cmd[l] = ft_dollar(list->full_cmd[l], &i, mini);
	else if (list->full_cmd[l][i] == '~')
		list->full_cmd[l] = ft_tilda(list->full_cmd[l], &i, mini);
	else if (list->full_cmd[l][i] == ' '
		&& list->full_cmd[l][i - 1] == ' ')
		list->full_cmd[l] = ft_space(list->full_cmd[l], &i);
	return (i);
}

void	parser(t_commands *list, t_mini *mini)
{
	int		i;
	int		l;

	l = -1;
	while (list->full_cmd[++l])
	{
		i = -1;
		while (list->full_cmd[l][++i])
		{
			if (list->full_cmd[l][i] == '\'' || list->full_cmd[l][i] == '\"')
			{
				if (list->full_cmd[l][i] == '\"')
					list->full_cmd[l]
						= ft_doublequot(list->full_cmd[l], &i, mini, 1);
				else
					list->full_cmd[l] = ft_onequot(list->full_cmd[l], &i);
				if (!list->full_cmd[l][0])
					break ;
			}
			else
				i = parser2(list, mini, i, l);
			if (!list->full_cmd[l][0])
				del_empty(list, &l);
		}
	}
}
