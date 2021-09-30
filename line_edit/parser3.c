/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:00:55 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:01:05 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_space(char *cmd, int *i)
{
	char	*before;
	char	*after;

	before = ft_substr(cmd, 0, *i);
	after = ft_strdup(cmd + (*i) + 1);
	--(*i);
	before = strjoin_free(before, after);
	free(after);
	free(cmd);
	return (before);
}

char	*ft_tilda(char *cmd, int *i, t_mini *mini)
{
	char	*after;
	char	*homeVal;

	if (*i && cmd[*i - 1] != ' ')
		return (cmd);
	if (cmd[*i + 1] && cmd[*i + 1] != ' ' && cmd[*i + 1] != '/')
		return (cmd);
	mini->tmpEnv = mini->envList;
	while (mini->tmpEnv)
	{
		if (!ft_strcmp(mini->tmpEnv->name, "HOME"))
			break ;
		mini->tmpEnv = mini->tmpEnv->next;
	}
	if (!mini->tmpEnv || !mini->tmpEnv->full[5])
		return (cmd);
	homeVal = ft_strdup(mini->tmpEnv->full + 5);
	after = ft_strdup(cmd + 1);
	*i += ft_strlen(homeVal);
	homeVal = strjoin_free(homeVal, after);
	free(after);
	free(cmd);
	return (homeVal);
}

void	del_empty(t_commands *list, int *l)
{
	int		size;
	int		num;
	char	*tmp;

	size = 0;
	while (list->full_cmd[size])
		++size;
	num = *l;
	tmp = list->full_cmd[num--];
	while (list->full_cmd[++num])
		list->full_cmd[num] = list->full_cmd[num + 1];
	free(tmp);
	--(*l);
}
