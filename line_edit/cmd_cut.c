/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:05:52 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 11:16:09 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* в случае если есть пайп зануляет двумерный массив в текущем
	листе , создает новый и меняет указатель на новый */

static void	stop_edit(t_mini *mini, int *i, int *num)
{
	char	*tmp;

	tmp = ft_strdup(mini->cmd + *i + 1);
	free(mini->cmd);
	mini->cmd = tmp;
	mini->cmdlist->full_cmd[*num] = NULL;
	*num = -1;
	mini->cmdlist->fPipeIn = 1;
	mini->tmplist = ft_lstnew(mini->num++);
	mini->tmplist->full_cmd = malloc(sizeof(char *) * (mini->args + 1));
	ft_lstadd_back(&mini->cmdlist, mini->tmplist);
	mini->cmdlist = mini->cmdlist->next;
	mini->cmdlist->fPipeIn = 0;
	mini->cmdlist->fPipeOut = 1;
	mini->cmdlist->redirFlag = 0;
	mini->cmdlist->fdIn = 0;
	mini->cmdlist->fdOut = 0;
	mini->cmdlist->stopWord = NULL;
}

int	skip_beforeQ(t_mini *mini, int i)
{
	char	symb;

	symb = mini->cmd[i];
	if (checkslash(mini, i, 0))
		while (mini->cmd[++i])
			if (mini->cmd[i] == symb)
				if (checkslash(mini, i, 1))
					break ;
	return (i);
}

static int	firstcmd2(t_mini *mini, int *num)
{
	int	i;
	int	tmp;

	i = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i] == '\'' || mini->cmd[i] == '\"')
			i = skip_beforeQ(mini, i);
		else if (mini->cmd[i] == ' ' || !mini->cmd[i])
		{
			tmp = i;
			while (tmp >= 0 && mini->cmd[tmp] == ' ')
				--tmp;
			if (tmp >= 0)
				break ;
		}
		else if (mini->cmd[i] == '|')
		{
			stop_edit(mini, &i, num);
			return (-1);
		}
		if (mini->cmd[i])
			++i;
	}
	return (i);
}

static void	firstcmd(t_mini *mini, int *num)
{
	int		i;
	int		start;
	char	*after;

	i = firstcmd2(mini, num);
	if (i == -1)
		return ;
	start = 0;
	while (mini->cmd[start] == ' ' && mini->cmd[start])
		++start;
	mini->cmdlist->full_cmd[*num] = ft_substr(mini->cmd, start, i - start);
	while (mini->cmd[i] == ' ' && mini->cmd[i])
		++i;
	after = ft_strdup(mini->cmd + i);
	free(mini->cmd);
	mini->cmd = after;
}

void	cut_cmd(t_mini *mini)
{
	int	i;
	int	start;
	int	cmd_num;

	i = 0;
	start = 0;
	cmd_num = 0;
	mini->cmdlist = ft_lstnew(mini->num++);
	mini->always1st = mini->cmdlist;
	mini->cmdlist->fRedir = NULL;
	mini->cmdlist->fPipeOut = 0;
	mini->cmdlist->fPipeIn = 0;
	mini->cmdlist->redirFlag = 0;
	mini->cmdlist->fdIn = 0;
	mini->cmdlist->fdOut = 0;
	mini->cmdlist->stopWord = NULL;
	mini->cmdlist->full_cmd = malloc(sizeof(char *) * (mini->args + 1));
	while (mini->cmd[0])
	{
		firstcmd(mini, &i);
		++i;
	}
	mini->cmdlist->full_cmd[i] = NULL;
}
