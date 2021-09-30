/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:00:14 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/29 14:51:41 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_itoa(int n)
{
	long	k;
	char	*ptr;

	k = n;
	n = ctr(k);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	ptr[n] = '\0';
	if (k < 0)
	{
		ptr[n - 1] = '-';
		k *= -1;
	}
	n = 0;
	if (k == 0)
		ptr[n++] = '0';
	while (k)
	{
		ptr[n++] = k % 10 + '0';
		k /= 10;
	}
	return (ft_strrev(ptr));
}

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static unsigned long long	ft_atoi_sifr(char *viv, int k)
{
	unsigned long long	res;
	unsigned long long	c;

	c = 1;
	res = 0;
	while (k > 0)
	{
		res = res + (viv[k - 1] - 48) * c;
		c = c * 10;
		k--;
		if (res >= 9223372036854775807)
			break ;
	}
	return (res);
}

unsigned long long	ft_atoi(const char *str)
{
	int		m;
	int		s;
	char	cifr[27];

	m = 1;
	s = 0;
	while (((*str > 8) && (*str < 14)) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			m = m * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		cifr[s] = *str;
		str++;
		s++;
	}
	return ((ft_atoi_sifr(cifr, s) * m));
}
