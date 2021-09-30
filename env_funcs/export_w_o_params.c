/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_w_o_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:44:52 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 15:03:15 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_backslash(t_mini *mini, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(mini->env_exp[i], 0, j + 1);
	tmp2 = mini->env_exp[i];
	mini->env_exp[i] = ft_strdup(tmp2 + j + 1);
	free(tmp2);
	tmp2 = mini->env_exp[i];
	mini->env_exp[i] = ft_strjoin("\"", tmp2);
	mini->env_exp[i] = strjoin_free(mini->env_exp[i], "\"");
	free(tmp2);
	tmp2 = mini->env_exp[i];
	mini->env_exp[i] = strjoin_free(tmp, tmp2);
	free(tmp2);
}

static void	backslash_giving(t_mini *mini)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (mini->env_exp[++i])
	{
		j = 0;
		while (mini->env_exp[i][j] != '=' && mini->env_exp[i][j])
			++j;
		if (!mini->env_exp[i][j])
			continue ;
		add_backslash(mini, i, j);
	}
}

static int	export_wop3(t_mini *mini, int i, int j)
{
	char	*tmp;

	while (mini->env_exp[i][j] == mini->env_exp[i + 1][j])
		++j;
	if (mini->env_exp[i][j] > mini->env_exp[i + 1][j]
		&& mini->env_exp[i][j] != '=' && mini->env_exp[i + 1][j] != '='
		&& mini->env_exp[i][j] && mini->env_exp[i + 1][j])
	{
		tmp = mini->env_exp[i];
		mini->env_exp[i] = mini->env_exp[i + 1];
		mini->env_exp[i + 1] = tmp;
		i = 0;
	}
	else if (mini->env_exp[i + 1][j] == '=' || !mini->env_exp[i + 1][j])
	{
		tmp = mini->env_exp[i];
		mini->env_exp[i] = mini->env_exp[i + 1];
		mini->env_exp[i + 1] = tmp;
		i = 0;
	}
	else
		i++;
	return (i);
}

static void	export_wop2(t_mini *mini, t_commands *list, int num)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (mini->env_exp[i + 1])
	{
		j = 0;
		if (mini->env_exp[i][j] > mini->env_exp[i + 1][j])
		{
			tmp = mini->env_exp[i];
			mini->env_exp[i] = mini->env_exp[i + 1];
			mini->env_exp[i + 1] = tmp;
			i = 0;
		}
		else if (mini->env_exp[i][j] == mini->env_exp[i + 1][j])
			i = export_wop3(mini, i, j);
		else
			++i;
	}
	backslash_giving(mini);
	export_wop_declare(mini, list, num);
}

void	export_wop(t_commands *list, int num, t_mini *mini)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = mini->envList;
	while (temp)
	{
		++i;
		temp = temp->next;
	}
	mini->env_exp = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	temp = mini->envList;
	while (temp)
	{
		if (temp->vision)
			mini->env_exp[i++] = ft_strdup(temp->full);
		temp = temp->next;
	}	
	mini->env_exp[i] = NULL;
	export_wop2(mini, list, num);
	mini->ff_exit = 0;
}
