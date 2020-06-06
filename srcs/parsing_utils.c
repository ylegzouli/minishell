/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:22:34 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/06 13:29:50 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			new_arg(char **s, char c)
{
	int		i;
	int		j;
	char	*old;

	old = ft_strdup(*s);
	i = 0;
	j = 0;
	free(*s);
	if (!((*s) = malloc(ft_strlen(old) - 1)))
		return (-1);
	(*s)[ft_strlen(old) - 2] = 0;
	while (old[i])
	{
		if (old[i] != c || j >= 2)
			(*s)[i - j] = old[i];
		else
			j++;
		i++;
	}
	free(old);
	return (0);
}

int			delete_quote2(char **s, int i, char c)
{
	int pos;

	pos = i;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	i++;
	if ((*s)[i])
	{
		while ((*s)[i] && (*s)[i] != c)
			i++;
		if ((*s)[i] && (*s)[i] == c && i < ft_strlen(*s))
			return (new_arg(s, c));
	}
	return (0);
}

void		delete_quote(char **arg)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup(*arg);
	free(*arg);
	while (s[i])
	{
		delete_quote2(&s, i, 39);
		delete_quote2(&s, i, '"');
		i++;
	}
	*arg = s;
}

void		get_arg(char **arg, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split_shell(str, '>');
	while (tmp[0][i] == ' ')
		i++;
	while (tmp[0][i] && tmp[0][i] != ' ')
		i++;
	while (tmp[0][i] == ' ')
		i++;
	*arg = ft_strtrim(&tmp[0][i], " ");
	free_split(tmp);
}
