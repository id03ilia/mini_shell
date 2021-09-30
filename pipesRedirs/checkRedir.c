/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkRedir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:04:10 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:58:36 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_commands *tmp, t_mini *mini)
{
	int	i;

	i = 0;
	while (tmp->full_cmd[i])
		++i;
	if (!i)
		return (0);
	i -= 1;
	if (!ft_strcmp(tmp->full_cmd[i], ">") || !ft_strcmp(tmp->full_cmd[i], ">>")
		||!ft_strcmp(tmp->full_cmd[i], "<")
		|| !ft_strcmp(tmp->full_cmd[i], "<"))
	{
		if (!mini->fakeHD)
		{
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token `newline\'\n", 2);
		}
		mini->ff_exit = 2;
		mini->fakeHD = 1;
		return (1);
	}
	return (0);
}
