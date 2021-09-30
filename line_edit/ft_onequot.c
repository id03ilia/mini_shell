/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onequot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:11:45 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/26 14:28:42 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_onequot(char *cmd, int *i)
{
	int		start;
	char	*before;
	char	*tmp;
	char	*after;

	start = *i;
	while (cmd[++(*i)])
		if (cmd[*i] == '\'')
			break ;
	before = ft_substr(cmd, 0, start);
	tmp = ft_substr(cmd, start + 1, *i - start - 1);
	after = ft_strdup(cmd + *i + 1);
	*i -= 2;
	before = strjoin_free(before, tmp);
	before = strjoin_free(before, after);
	free(tmp);
	free(after);
	free(cmd);
	return (before);
}
