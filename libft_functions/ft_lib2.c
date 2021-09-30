/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:57:49 by dflorenc          #+#    #+#             */
/*   Updated: 2021/09/28 17:16:02 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (size_t) start)
		len = 0;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (NULL);
	len += (size_t) start;
	while ((size_t) start < len)
		s1[i++] = s[start++];
	s1[i] = '\0';
	return (s1);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (!(ft_strlen(needle)) || (needle == NULL && haystack == NULL))
		return ((char *) haystack);
	while (*haystack)
	{
		i = 0;
		while (*haystack != *needle && *haystack)
			haystack++;
		if (*haystack == *needle && *haystack)
		{
			while (*needle && *haystack == *needle && ++i)
				if (*haystack++ == *needle)
					needle++;
			if (*needle == '\0')
				return ((char *) haystack - i);
			needle -= i;
			if (i)
				haystack -= i - 1;
		}
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*c;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc(sizeof(char) * (i + 1));
	if (!c)
		return (NULL);
	i = 0;
	while (*s1)
		c[i++] = *s1++;
	while (*s2)
		c[i++] = *s2++;
	c[i] = '\0';
	return (c);
}

char	*strjoin_free(char *s1, char *s2)
{
	size_t	l;
	size_t	j;
	size_t	s1_count;
	size_t	s2_count;
	char	*arr;

	if (!s1 && !s2)
		return (NULL);
	l = -1;
	j = 0;
	s1_count = ft_strlen(s1);
	s2_count = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (s1_count + s2_count + 1));
	if (!arr)
		return (NULL);
	while (++l < s1_count)
		arr[l] = s1[l];
	while (j < s2_count)
		arr[l++] = s2[j++];
	arr[l] = '\0';
	if (s1)
		free (s1);
	return (arr);
}

int	ft_strcmp_f(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (*s1 || *s2)
	{
		if (*s1 != *s2 && *s1 != *s2 - 32 && *s1 != *s2 + 32)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
