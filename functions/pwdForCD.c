/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwdForCD.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:58:47 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/28 11:59:51 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cmd_cd2(char *cmd)
{
	char	*buf;
	char	*tmp;

	buf = malloc(sizeof(char) * 1000);
	getcwd(buf, 1000);
	tmp = buf;
	buf = ft_strjoin(cmd, tmp);
	free(tmp);
	return (buf);
}
