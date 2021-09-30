/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:40:08 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:08:21 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_next_line(char **line, int fd)
{
	char	*buf;
	int		i;
	int		res;
	char	ch;

	buf = malloc(sizeof(char) * 4096);
	if (!buf)
		return (-1);
	i = 0;
	ch = '\0';
	*line = buf;
	res = 1;
	while (res > 0 && ch != '\n' && i < 4095)
	{
		res = read(fd, &ch, 1);
		buf[i++] = ch;
	}
	buf[i] = '\0';
	return (res);
}

void	history_rd(t_mini *mini)
{
	char	*line;

	mini->fdH = open(".history", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (mini->fdH < 0)
	{
		ft_putstr_fd("\"history\"file reading error\n", 2);
		exit (-1);
	}
	while (get_next_line(&line, mini->fdH) != 0)
	{
		add_history(line);
		free(line);
	}
	free(line);
}

void	history_wr(char *cmd, int fd)
{
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
}
