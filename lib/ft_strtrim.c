/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:28:10 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/07 11:20:56 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	while (*set)
	{
		if (c == (char)*set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_strnull(void)
{
	char *s;

	s = malloc(1);
	s[0] = 0;
	return (s);
}

static int	ft_init(char **s, int *a, int *b)
{
	*s = 0;
	*a = 0;
	*b = 0;
	return (1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		len;
	int		i;

	if (ft_init(&s2, &len, &i) && (s1 == 0 || set == 0))
		return (ft_strnull());
	while (*s1 && ft_isset(*s1, set))
		s1++;
	i = 0;
	len = 0;
	while (s1[i])
	{
		while (s1[i] && !ft_isset(s1[i], set))
			i++;
		len = i;
		while (s1[i] && ft_isset(s1[i], set))
			i++;
	}
	if (!(s2 = malloc(1 + len)))
		return (0);
	i = -1;
	while (++i < len)
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}
