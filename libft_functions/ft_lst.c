/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:51:59 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/28 17:16:07 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*ft_lstnew(int content)
{
	t_commands	*the_new;

	the_new = (t_commands *)malloc(sizeof(t_commands));
	if (!the_new)
		return (NULL);
	the_new->num = content;
	the_new->next = NULL;
	return (the_new);
}

t_commands	*ft_lstlast(t_commands *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_commands **lst, t_commands *new)
{
	t_commands	*ptr;

	if (new == NULL)
		return ;
	else if (*lst == NULL || lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}
