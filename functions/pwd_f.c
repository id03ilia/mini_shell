/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dflorenc <dflorenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:02:31 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 09:20:57 by dflorenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_f(t_commands *list, int num, t_mini *mini)
{
	char	*buf;
	int		tmp;

	tmp = 1;
	if (list->fPipeIn)
		tmp = mini->dd[num][1];
	if (list->redirFlag)
		tmp = list->fdOut;
	buf = malloc(sizeof(char) * 1000), getcwd(buf, 1000);
	if (!buf[0])
	{
		mini->tmpEnv = mini->envList;
		while (mini->tmpEnv)
		{
			if (!ft_strcmp(mini->tmpEnv->name, "PWD"))
				break ;
			mini->tmpEnv = mini->tmpEnv->next;
		}
		if (mini->tmpEnv)
			ft_putstr_fd(mini->tmpEnv->full + 4, tmp);
	}
	else
		ft_putstr_fd(buf, tmp);
	write(tmp, "\n", 1), free(buf), buf = NULL;
	mini->ff_exit = 0;
}
