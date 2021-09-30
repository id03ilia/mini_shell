/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:54:08 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:24:51 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	noParams(t_mini *mini)
{
	mini->tmpEnv = mini->envList;
	while (mini->tmpEnv && ft_strcmp(mini->tmpEnv->name, "HOME"))
		mini->tmpEnv = mini->tmpEnv->next;
	if (!mini->tmpEnv || !mini->tmpEnv->full[4] || !mini->tmpEnv->full[5])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		mini->ff_exit = 1;
		return (1);
	}
	return (0);
}

static int	OldDir(t_commands *list, t_mini *mini)
{
	mini->tmpEnv = mini->envList;
	while (mini->tmpEnv && ft_strcmp(mini->tmpEnv->name, "OLDPWD"))
		mini->tmpEnv = mini->tmpEnv->next;
	if (!mini->tmpEnv || !mini->tmpEnv->full[6])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		mini->ff_exit = 1;
		return (1);
	}
	free (list->full_cmd[1]);
	list->full_cmd[1] = ft_strdup(mini->tmpEnv->full + 7);
	printf("%s\n", list->full_cmd[1]);
	return (0);
}

static void	second_part(t_mini *mini, t_commands *list, int flag, int i)
{
	char		*buf;
	t_commands	*new;

	buf = cmd_cd2("OLDPWD=");
	new = ft_lstnew(1);
	new->full_cmd = malloc(sizeof(char *) * 3);
	new->full_cmd[0] = ft_strdup("1");
	new->full_cmd[1] = buf;
	new->full_cmd[2] = NULL;
	export_f(mini, new, 1);
	if (flag)
	{
		if (chdir(list->full_cmd[1]) == -1)
			ft_putstr_fd(strerror (errno), 2);
	}
	else
		if (chdir(mini->tmpEnv->full + 5) == -1)
			ft_putstr_fd(strerror (errno), 2);
	buf = cmd_cd2("PWD="), free(new->full_cmd[1]);
	new->full_cmd[1] = buf, export_f(mini, new, 1);
	while (new->full_cmd[i])
		free(new->full_cmd[i++]);
	free(new->full_cmd), free(new);
}

static int	first_part(t_commands *list, t_mini *mini, int *flag)
{
	if (!list->full_cmd[1])
	{
		*flag = noParams(mini);
		if (*flag)
			return (1);
	}
	else if (list->full_cmd[1][0] == '-' && !list->full_cmd[1][1])
	{
		if (OldDir(list, mini))
			return (1);
	}
	else if (list->full_cmd[1][0] == '~' && (list->full_cmd[1][1] == '/'
		|| !list->full_cmd[1][1]))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		mini->ff_exit = 1;
		return (1);
	}
	return (0);
}

void	cmd_cd(t_commands *list, t_mini *mini)
{
	DIR		*Dir;
	int		flag;

	flag = 1;
	mini->ff_exit = 0;
	if (first_part(list, mini, &flag))
		return ;
	if (flag)
		Dir = opendir(list->full_cmd[1]);
	else
		Dir = opendir(mini->tmpEnv->full + 5);
	if ((Dir) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (flag)
			ft_putstr_fd(list->full_cmd[1], 2);
		else
			ft_putstr_fd(mini->tmpEnv->full + 5, 2);
		write(2, " : ", 3);
		ft_putstr_fd(strerror (errno), 2);
		write(2, "\n", 1), mini->ff_exit = 1;
		return ;
	}
	second_part(mini, list, flag, 0), closedir(Dir);
}
