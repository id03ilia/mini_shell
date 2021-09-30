/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:59:07 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:54:54 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*miniparser(char *cmd, int num, t_mini *mini)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"')
			cmd = ft_doublequot(cmd, &i, mini, num);
		else if (cmd[i] == '\'')
			cmd = ft_onequot(cmd, &i);
		else if (cmd[i] == '$' && num)
			cmd = ft_dollar(cmd, &i, mini);
		else if (cmd[i] == '~' && num)
			cmd = ft_tilda(cmd, &i, mini);
	}
	return (cmd);
}
