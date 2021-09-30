/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:07:29 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:55:04 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (0);
	return (1);
}

static int	ft_isittrue(t_env *temp, char *tmp)
{
	int	z;

	z = ft_strlen(temp->name);
	if (ft_strcmp(temp->name, tmp) == 0)
		return (z);
	return (-1);
}

static char	*cut_dollar(char *str, char *value, int start)
{
	char	*before;
	char	*after;

	before = ft_substr(str, 0, start);
	while (str[++start])
		if (is_key(str[start]))
			break ;
	after = ft_strdup(str + start);
	before = strjoin_free(before, value);
	before = strjoin_free(before, after);
	free(after);
	if (value[0])
		free(value);
	return (before);
}

static char	*ft_dollar2(t_mini *mini, char *tmp, int *i)
{
	char	*value;
	t_env	*temp;
	int		z;

	temp = mini->envList;
	while (temp)
	{
		if (ft_strstr(temp->name, tmp))
		{
			z = ft_isittrue(temp, tmp);
			if (z != -1)
				break ;
		}
		temp = temp->next;
	}
	value = "\0";
	if (temp)
		value = ft_substr(temp->full, z + 1, ft_strlen(temp->full) - z);
	(*i) += ft_strlen(value);
	return (value);
}

char	*ft_dollar(char *cmd, int *i, t_mini *mini)
{
	int		start;
	char	*value;
	char	*tmp;

	start = *i;
	if (cmd[*i + 1] == '?' || ft_isdigit(cmd[*i + 1]))
	{
		if (cmd[*i + 1] == '?')
			value = ft_question(mini, cmd, i);
		else
			value = dig_edit(cmd, i);
		free(cmd);
		return (value);
	}
	while (cmd[++(*i)])
		if (is_key(cmd[*i]))
			break ;
	if (*i == start + 1 && (*i)--)
		return (cmd);
	tmp = ft_substr(cmd, start + 1, *i - start - 1);
	(*i) = (start - 1);
	value = ft_dollar2(mini, tmp, i);
	value = cut_dollar(cmd, value, start), free(tmp), free(cmd);
	return (value);
}
