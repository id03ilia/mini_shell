/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:48:32 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:49:23 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*this_pwd(char *cmd)
{
	char	*buf;

	buf = malloc(1000);
	getcwd(buf, 1000);
	buf = strjoin_free(buf, cmd);
	free(cmd);
	return (buf);
}

void	edit_first(t_commands *list, int *flag)
{
	char	*tmp;
	int		i;

	i = 1;
	*flag = 1;
	while (list->full_cmd[0][i] == '/')
		++i;
	tmp = ft_strdup(list->full_cmd[0] + i - 1);
	tmp = this_pwd(tmp);
	free(list->full_cmd[0]);
	list->full_cmd[0] = tmp;
}

void	shlvl_edit(char **env)
{
	int	i;
	int	val;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL", 5))
		++i;
	if (!env[i])
	{
		env[i] = ft_strdup("SHLVL=1");
		env[i + 1] = NULL;
		return ;
	}
	else if (!env[i][5] || !env[i][6])
	{
		free(env[i]), env[i] = ft_strdup("SHLVL=1");
		return ;
	}
	else
	{
		val = (int)ft_atoi(env[i] + 6);
		if (val < 0)
			val = -1;
		free(env[i]);
		env[i] = ft_strjoin("SHLVL=", ft_itoa(val + 1));
	}
}
