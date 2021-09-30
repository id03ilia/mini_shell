/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isHeredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:55:41 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 16:56:24 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isHeredoc(t_commands *list, t_mini *mini)
{
	int	i;

	i = 0;
	while (list->full_cmd[i] && ft_strcmp(list->full_cmd[i], "<<"))
		++i;
	if (!list->full_cmd[i] || !list->full_cmd[i + 1])
		return (0);
	list->redirFlag = 4;
	if (list->stopWord != NULL)
		free(list->stopWord);
	list->stopWord = miniparser(ft_strdup(list->full_cmd[i + 1]), 0, mini);
	list->full_cmd = cmd_remalloc(list->full_cmd, i);
	isHeredoc(list, mini);
	return (1);
}
