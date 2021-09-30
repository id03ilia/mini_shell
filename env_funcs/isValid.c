/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:46:53 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/23 17:46:54 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_exp(t_commands *list, int i)
{
	int	j;

	j = 1;
	if (!ft_isalpha(list->full_cmd[i][0]) && list->full_cmd[i][0] != '_')
		return (i);
	while (list->full_cmd[i][j] != '=' && list->full_cmd[i][j] != '+'
		&& list->full_cmd[i][j])
	{
		if (!ft_isalnum(list->full_cmd[i][j]) && list->full_cmd[i][j] != '_')
			return (i);
		++j;
	}
	if (list->full_cmd[i][j] == '+' && list->full_cmd[i][j + 1] != '=')
		return (i);
	return (0);
}

int	is_valid_uns(t_commands *list, int i)
{
	int	j;

	j = 0;
	if (!ft_isalpha(list->full_cmd[i][0]) && list->full_cmd[i][0] != '_')
		return (1);
	while (list->full_cmd[i][++j])
		if (!ft_isalnum(list->full_cmd[i][j]) && list->full_cmd[i][j] != '_')
			return (1);
	return (0);
}
