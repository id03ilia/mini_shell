/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:12:27 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/23 18:12:28 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_slash(char *cmd, int *i)
{
	char	*before;
	char	*after;

	before = ft_substr(cmd, 0, *i);
	after = ft_strdup(cmd + (*i) + 1);
	before = strjoin_free(before, after);
	free(after);
	free(cmd);
	return (before);
}
