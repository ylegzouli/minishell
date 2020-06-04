/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/04 17:27:53 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			count_char(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

void		direction_cd(char **s)
{
	int		i;
	char	*res;
	int		j;

	i = 2;
	j = 0;
	while ((*s)[i] && (*s)[i] == ' ')
		i++;
	if ((*s)[i] != '<' ||
	!(res = malloc(ft_strlen(*s) + 1 - count_char(*s, '<'))))
		return ;
	i = 0;
	while ((*s)[i + j])
	{
		if ((*s)[i + j] != '<')
		{
			res[i] = (*s)[i + j];
			i++;
		}
		else
			j++;
	}
	res[ft_strlen(*s) - count_char(*s, '<')] = '\0';
	free(*s);
	*s = res;
}

int			check_err(char *str)
{
	char	*tmp;
	int		i;

	i = 1;
	if ((tmp = ft_strchr_shell(str, '>')) != NULL)
	{
		if (tmp[1] && tmp[2] && tmp[1] == '>' && tmp[2] == '>')
			return (1);
		if (tmp[1] && tmp[1] == ' ')
		{
			while (tmp[i] && tmp[i] == ' ')
				i++;
			if (tmp[i] && tmp[i] == '>')
				return (1);
		}
	}
	return (0);
}

int			check_err_bis(char *str)
{
	char	*tmp;
	int		i;

	i = 1;
	if ((tmp = ft_strchr_shell(str, '<')) != NULL)
	{
		if (tmp[1] && tmp[1] == '<')
			return (1);
		if (tmp[1] && tmp[1] == ' ')
		{
			while (tmp[i] && tmp[i] == ' ')
				i++;
			if (tmp[i] && tmp[i] == '<')
				return (1);
		}
	}
	return (0);
}
