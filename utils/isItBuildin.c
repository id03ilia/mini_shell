/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isItBuildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:25:03 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:52:39 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_hidden_env(t_commands *list)
{
	int		i;
	int		num;
	char	**tmp;

	i = 0;
	while (list->full_cmd[i] && ft_strstr(list->full_cmd[i], "="))
		++i;
	if (!list->full_cmd[i])
		return (1);
	num = i++;
	while (list->full_cmd[i])
		++i;
	tmp = malloc(sizeof(char *) * (i - num + 1));
	i = 0;
	while (list->full_cmd[num])
		tmp[i++] = ft_strdup(list->full_cmd[num++]);
	tmp[i] = NULL;
	i = -1;
	while (list->full_cmd[++i])
		free(list->full_cmd[i]);
	free(list->full_cmd);
	list->full_cmd = tmp;
	return (0);
}

static int	buildinP2(t_commands *list, t_mini *mini, int num)
{
	if (!ft_strcmp_f(list->full_cmd[0], "export"))
	{
		if (list->full_cmd[1])
			export_f(mini, list, 1);
		else
			export_wop(list, num, mini);
	}
	else if (!ft_strcmp_f(list->full_cmd[0], "unset"))
		unset_f(mini, list);
	else if (!ft_strcmp_f(list->full_cmd[0], "env"))
		env_f(list, num, mini);
	else if (!ft_strcmp_f(list->full_cmd[0], "exit"))
		exit_f(list, mini);
	else if (ft_strstr(list->full_cmd[0], "=") && check_hidden_env(list))
		export_f(mini, list, 0);
	else
		return (1);
	return (0);
}

int	isItBuildin(t_commands *list, int num, t_mini *mini)
{	
	if (!list->full_cmd[0] || !list->full_cmd[0][0])
		num += 0;
	else if (!ft_strcmp_f(list->full_cmd[0], "pwd"))
		pwd_f(list, num, mini);
	else if (!ft_strcmp_f(list->full_cmd[0], "echo"))
		echo_f(list, num, mini);
	else if (!ft_strcmp_f(list->full_cmd[0], "cd"))
		cmd_cd(list, mini);
	else
		if (buildinP2(list, mini, num))
			return (0);
	mini->lastCMD = 1;
	return (1);
}
