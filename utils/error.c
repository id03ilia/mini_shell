/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:36:35 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/28 17:01:21 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	std_error(int fd, char *str_err, char *name)
{
	write(fd, str_err, ft_strlen(str_err));
	write(fd, ": ", 2);
	write(fd, name, ft_strlen(name));
	write(fd, "\n", 1);
	exit(1);
}

void	free_mass(char **mas)
{
	int	y;

	y = 0;
	if (mas)
	{
		while (mas[y])
		{
			free(mas[y]);
			mas[y] = NULL;
			y++;
		}
		free(mas);
		mas = NULL;
	}
}

void	free_mass_int_pipe(int **mas, int c)
{
	int	y;

	y = 0;
	while (y < c)
	{
		free(mas[y]);
		mas[y] = NULL;
		y++;
	}
	free(mas);
	mas = NULL;
}
