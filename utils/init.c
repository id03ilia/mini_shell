/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:04:26 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 15:04:41 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init(t_mini *mini, char **env, char **argv, int argc)
{
	(void)argc;
	(void)argv;
	mini->cmdlist = NULL;
	mini->tmplist = NULL;
	mini->declare = ft_strdup("declare -x ");
	mini->num = 0;
	mini->ff_exit = 0;
	mini->fakeHD = 0;
	mini->dd = NULL;
	putEnvList(mini, env);
	history_rd(mini);
}
