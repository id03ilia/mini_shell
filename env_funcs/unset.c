/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:49:59 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 09:22:06 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_f2(t_env *temp, t_env *temp2, t_mini *mini, char *tmp)
{
	while (temp)
	{
		if (ft_strcmp(temp->name, tmp) == 0)
			break ;
		temp2 = temp;
		temp = temp->next;
	}
	if (temp)
	{
		if (temp != mini->env1st)
			temp2->next = temp->next;
		else
			mini->envList = mini->envList->next;
		free(temp->name);
		free(temp->full);
		free(temp);
	}
}

void	unset_f(t_mini *mini, t_commands *list)
{
	int		i;
	int		j;
	char	*tmp;
	t_env	*temp;
	t_env	*temp2;

	i = 0;
	mini->ff_exit = 0;
	while (list->full_cmd[++i])
	{
		if (is_valid_uns(list, i))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(list->full_cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			mini->ff_exit = 1;
			continue ;
		}
		j = 0;
		temp = mini->envList;
		j = ft_strlen(list->full_cmd[i]);
		tmp = ft_substr(list->full_cmd[i], 0, j);
		temp2 = temp, unset_f2(temp, temp2, mini, tmp);
		free(tmp);
	}
}
