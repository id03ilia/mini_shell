/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putEnvList.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:48:34 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/23 17:48:59 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_oldpwd(t_mini *mini)
{
	t_env	*tmp;

	tmp = ft_lstnew1();
	tmp->name = ft_strdup("OLDPWD");
	tmp->full = ft_strdup("OLDPWD");
	tmp->vision = 1;
	ft_lstadd_back1(&mini->envList, tmp);
}

void	putEnvList(t_mini *mini, char **env)
{
	t_env	*tmp;
	int		flag;
	int		i;
	int		j;

	i = -1;
	flag = 1;
	while (env[++i])
	{
		j = 0;
		tmp = ft_lstnew1();
		while (env[i][j] && env[i][j] != '=')
			++j;
		tmp->name = ft_substr(env[i], 0, j);
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			flag = 0;
		tmp->full = ft_strdup(env[i]);
		tmp->vision = 1;
		ft_lstadd_back1(&mini->envList, tmp);
	}
	if (flag)
		put_oldpwd(mini);
}
