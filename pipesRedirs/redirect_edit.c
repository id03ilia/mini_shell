/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:57:35 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 13:54:19 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_edit1(t_commands *line, int num, int i, t_mini *mini)
{
	line->full_cmd[i + 1] = miniparser(line->full_cmd[i + 1], 1, mini);
	if (num == 1)
		line->fdOut = open(line->full_cmd[i + 1],
				O_RDWR | O_TRUNC | O_CREAT, 0664);
	else if (num == 2)
		line->fdOut = open(line->full_cmd[i + 1],
				O_RDWR | O_APPEND | O_CREAT, 0664);
	else if (num == 3)
		line->fdIn = open(line->full_cmd[i + 1], O_RDONLY);
	if (line->fdIn < 0 || line->fdOut < 0 || read(line->fdIn, 0, 0) < 0
		|| read(line->fdOut, 0, 0) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(line->full_cmd[i + 1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	line->redirFlag = num;
	line->full_cmd = cmd_remalloc(line->full_cmd, i);
	return (0);
}

int	redir_edit(t_commands *line, t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line->full_cmd[i] && line->full_cmd[i][0] != '>'
		&& line->full_cmd[i][0] != '<')
		++i;
	if (!line->full_cmd[i])
		return (0);
	if (line->full_cmd[i][0] == '>' && !line->full_cmd[i][1])
		j = 1;
	else if (line->full_cmd[i][0] == '>' && line->full_cmd[i][1] == '>')
		j = 2;
	else if (line->full_cmd[i][0] == '<' && !line->full_cmd[i][1])
		j = 3;
	if (redir_edit1(line, j, i, mini))
		return (1);
	return (redir_edit(line, mini));
}
