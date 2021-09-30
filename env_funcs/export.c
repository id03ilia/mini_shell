/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:45:21 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 09:22:28 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_cmd(t_mini *mini, t_commands *list, int check, int i)
{
	t_env	*temp;
	char	*forfree;

	temp = mini->envList;
	if (check - 1 >= 0 && list->full_cmd[i][check - 1] == '+')
		--check;
	while (temp)
	{
		if (temp->name[check] == '\0')
		{
			forfree = ft_substr(list->full_cmd[i], 0, check);
			if (!ft_strcmp(temp->name, forfree))
			{
				free (forfree);
				break ;
			}
			free(forfree);
		}
		temp = temp->next;
	}
	return (temp);
}

static void	export_wCmd(int check, t_commands *list, t_env *temp, int i)
{
	char	*tmp;

	if (check - 1 >= 0 && list->full_cmd[i][check - 1] == '+')
	{
		tmp = ft_strdup(list->full_cmd[i] + check + 1);
		temp->full = strjoin_free(temp->full, tmp);
		free(tmp);
		return ;
	}
	if (!temp->vision)
		if (!ft_strcmp(list->full_cmd[0], "export"))
			temp->vision = 1;
	free(temp->full);
	temp->full = ft_strdup(list->full_cmd[i]);
	return ;
}

static void	export_f1(t_mini *mini, t_commands *list, int check, int i)
{
	t_env	*temp;
	char	*tmp;

	temp = find_cmd(mini, list, check, i);
	if (temp)
	{
		export_wCmd(check, list, temp, i);
		return ;
	}
	temp = ft_lstnew1();
	if (check - 1 >= 0 && list->full_cmd[i][check - 1] == '+')
		--check;
	temp->name = ft_substr(list->full_cmd[i], 0, check);
	if (list->full_cmd[i][check] == '+')
	{
		tmp = ft_strdup(list->full_cmd[i] + check + 1);
		temp->full = ft_strjoin(temp->name, tmp);
		free(tmp);
	}
	else
		temp->full = ft_strdup(list->full_cmd[i]);
	temp->vision = 0;
	if (!ft_strcmp(list->full_cmd[0], "export"))
		temp->vision = 1;
	ft_lstadd_back1(&mini->envList, temp);
}

static void	export_f2(t_mini *mini, t_commands *list, int check, int i)
{
	t_env	*temp;
	char	*forfree;

	temp = mini->envList;
	while (temp)
	{
		if (temp->name[check] == '\0')
		{
			forfree = ft_substr(list->full_cmd[i], 0, check);
			if (!ft_strcmp(temp->name, forfree))
				break ;
			free(forfree);
		}
		temp = temp->next;
	}
	if (!temp)
	{
		temp = ft_lstnew1();
		temp->name = ft_substr(list->full_cmd[i], 0, check);
		temp->full = ft_strdup(list->full_cmd[i]);
		temp->vision = 1, ft_lstadd_back1(&mini->envList, temp);
	}
	else
		temp->vision = 1, free(forfree);
}

void	export_f(t_mini *mini, t_commands *list, int num)
{
	int		i;
	int		check;

	i = num;
	mini->ff_exit = 0;
	while (list->full_cmd[i])
	{
		if (is_valid_exp(list, i) != 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(list->full_cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			mini->ff_exit = 1;
			++i;
			continue ;
		}
		check = 0;
		while (list->full_cmd[i][check] != '=' && list->full_cmd[i][check])
			++check;
		if (list->full_cmd[i][check])
			export_f1(mini, list, check, i++);
		else
			export_f2(mini, list, check, i++);
	}
}
