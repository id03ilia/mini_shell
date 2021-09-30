/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublequot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:11:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:16:46 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_dq2(char *cmd, int start, int *i)
{
	char	*before;
	char	*tmp;
	char	*after;

	before = ft_substr(cmd, 0, start);
	tmp = ft_substr(cmd, start + 1, *i - start - 1);
	after = ft_strdup(cmd + *i + 1);
	before = strjoin_free(before, tmp);
	before = strjoin_free(before, after);
	(*i) -= 1;
	if (before[0])
		(*i) -= 1;
	free(tmp);
	free(after);
	free(cmd);
	return (before);
}

char	*ft_doublequot(char *cmd, int *i, t_mini *mini, int num)
{
	int		start;

	start = *i;
	while (cmd[++(*i)])
	{
		if (cmd[*i] == '\"')
			break ;
		else if (cmd[*i] == '$' && num)
			cmd = ft_dollar(cmd, i, mini);
		else if (cmd[*i] == '\\' && (cmd[*i + 1] == '\"'
				|| cmd[*i + 1] == '$' || cmd[*i + 1] == '\\'))
			cmd = ft_slash(cmd, i);
	}
	return (ft_dq2(cmd, start, i));
}
