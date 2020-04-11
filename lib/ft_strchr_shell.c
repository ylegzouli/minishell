/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:15:28 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/07 11:52:55 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int      ft_is_sep(const char *str, char c2, char *quote, int i)
{
    if (str[i] == *quote)
        *quote = 0;
    else if (*quote == 0 && (str[i] == '"' || str[i] == 39))
        *quote = str[i];
    if (i > 0 && str[i - 1] == 92)
        return (0);
    if (str[i] == c2 && *quote == 0)
        return (1);
    return (0);
}

char		*ft_strchr_shell(char const *s, int c)
{
	int		i;
	char	*tmp;
	char	quote;

	i = 0;
	quote = 0;
	tmp = (char *)s;
	while (tmp[i] != '\0')
	{
		if (ft_is_sep(s, c, &quote, i))
			return (&tmp[i]);
		i++;
	}
	if (ft_is_sep(s, c, &quote, i))
		return (&tmp[i]);
	return (NULL);
}
