/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:55:12 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:55:29 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_question(t_mini *mini, char *cmd, int *i)
{
	char	*before;
	char	*tmp;
	char	*after;

	before = ft_substr(cmd, 0, *i);
	tmp = ft_itoa(mini->ff_exit);
	after = ft_strdup(cmd + *i + 2);
	before = strjoin_free(before, tmp);
	before = strjoin_free(before, after);
	*i = *i + ft_strlen(tmp) - 1;
	free(after);
	free(tmp);
	return (before);
}

char	*dig_edit(char *cmd, int *i)
{
	char	*before;

	before = ft_substr(cmd, 0, *i);
	return (strjoin_free(before, cmd + *i + 2));
}
