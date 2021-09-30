/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remalloc_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:35:53 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/28 16:54:44 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmd_remalloc(char **old_mas, int i)
{
	int		y;
	int		j;
	char	**new;

	y = 0;
	j = 0;
	while (old_mas[y])
		y++;
	new = (char **)malloc(sizeof(char *) * y - 1);
	y = 0;
	while (old_mas[y])
	{
		if (y == i)
			y += 2;
		if (!old_mas[y])
			break ;
		new[j++] = ft_strdup(old_mas[y++]);
	}
	new[j] = NULL;
	y = 0;
	while (old_mas[y])
		free(old_mas[y++]);
	free(old_mas);
	return (new);
}
