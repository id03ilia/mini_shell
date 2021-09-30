/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:54:25 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/28 17:16:09 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew1(void)
{
	t_env	*the_new;

	the_new = (t_env *)malloc(sizeof(t_env));
	if (!the_new)
		return (NULL);
	the_new->next = NULL;
	return (the_new);
}

t_env	*ft_lstlast1(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back1(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (new == NULL)
		return ;
	else if (*lst == NULL || lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_lstlast1(*lst);
		ptr->next = new;
	}
}
