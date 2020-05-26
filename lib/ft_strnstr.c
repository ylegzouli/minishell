/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:02:53 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/07 11:45:30 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int pos;
	unsigned int i;

	if (!*to_find)
		return ((char*)str);
	pos = 0;
	while (str[pos] != '\0' && (size_t)pos < len)
	{
		if (str[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && str[pos + i] == to_find[i] &&
					(size_t)(pos + i) < len)
				++i;
			if (to_find[i] == '\0')
				return ((char*)&str[pos]);
		}
		++pos;
	}
	return (0);
}
