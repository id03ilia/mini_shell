/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:00:24 by aeldridg          #+#    #+#             */
/*   Updated: 2021/09/29 14:51:19 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_check_digit(t_commands *list, int *y, int ch)
{
	while (list->full_cmd[1][*y])
	{
		if (!ft_isdigit(list->full_cmd[1][*y]))
			ch = 1;
		*y = *y + 1;
	}
	return (ch);
}

static void	exit_f_2cmd(t_commands *list, t_mini *mini, int y, int minus)
{
	int					ch;
	unsigned long long	Ld;

	g_ff_exit = 0;
	ch = 0;
	ch = exit_check_digit(list, &y, ch);
	Ld = ft_atoi(list->full_cmd[1]);
	if (ch || (Ld > 9223372036854775807 && minus == 1)
		|| ((Ld <= 9223372036854775807 && minus == -1)))
	{
		write(2, "minishell: exit: ", 17);
		write(2, list->full_cmd[1], ft_strlen(list->full_cmd[1]));
		write(2, ": numeric argument required\n", 29);
		mini->ff_exit = 255;
	}
	else
	{
		if (minus)
			mini->ff_exit = (int)(Ld % 256);
		else
			mini->ff_exit = (256 + (int)Ld % 256) % 256;
	}
}

static int	exit_check_symb_minus(t_commands *list, int y, int *minus)
{
	if (list->full_cmd[1][0] == '-')
	{
		*minus = *minus *-1;
		y++;
	}
	if (list->full_cmd[1][0] == '+')
		y++;
	return (y);
}

void	exit_f(t_commands *list, t_mini *mini)
{
	int					i;
	int					y;
	int					minus;

	i = 0;
	minus = 1;
	write(2, "exit\n", 5);
	while (list->full_cmd[i])
		i++;
	if (i >= 3)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		mini->ff_exit = 1;
		return ;
	}
	if (i == 2)
	{
		y = 0;
		y = exit_check_symb_minus(list, y, &minus);
		exit_f_2cmd(list, mini, y, minus);
	}
	exit(mini->ff_exit);
}
