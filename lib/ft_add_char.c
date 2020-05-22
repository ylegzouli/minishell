/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 17:57:16 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/22 18:05:57 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*ft_add_char(char *str, char c)
{
	size_t		len;
	char		*tmp;
	int			i;

	i = 0;
	len = 0;
	if (str)
		len = ft_strlen(str);
	tmp = malloc(len + 2);
	while (str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len] = c;
	tmp[len + 1] = 0;
	if (str)
		free(str);
	return (tmp);
}
