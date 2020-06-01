/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:18:10 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/01 20:41:59 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			find_space(char c)
{
	if (c == 'b')
		return (8);
	if (c == 't')
		return (9);
	if (c == 'r')
		return (13);
	if (c == 'e')
		return (27);
	if (c == 92)
		return (92);
	if (c == 'n')
		return (10);
	if (c == 'v')
		return (11);
	else
		return (12);
}

int			bslash_found(char **result, int pos)
{
	int		i;
	char	*temp;

	i = -1;
	if (!(temp = malloc(ft_strlen(*result))))
		return (1);
	temp[ft_strlen(*result) - 1] = '\0';
	while (++i < pos)
		temp[i] = (*result)[i];
	temp[i] = find_space((*result)[i + 1]);
	while ((*result)[++i + 1])
		temp[i] = (*result)[i + 1];
	free(*result);
	*result = temp;
	return (0);
}

int			react_with_bslash(char c)
{
	if (c == 'n' || c == 'v' || c == 'f' || c == 't')
		return (1);
	if (c == 'b' || c == 'r' || c == 'e' || c == 92)
		return (1);
	return (0);
}

int			look_for_back_slash(char **result)
{
	int		i;
	char	*ret;

	i = 0;
	while ((*result)[i])
	{
		while ((*result)[i] && (*result)[i] != 92)
			i++;
		if ((*result)[i] && (*result)[i + 1] &&
		react_with_bslash((*result)[i + 1]) == 1)
		{
			bslash_found(result, i);
			i = -1;
		}
		i++;
	}
	return (0);
}
