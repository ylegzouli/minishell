/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:55:36 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/01 19:58:58 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			n_inside_q(char *s, int i)
{
	int		j;
	int		k;
	char	c;

	j = 0;
	while (s[j] && s[j] != '"' && s[j] != 39)
		j++;
	k = j;
	if (s[j])
		c = s[j];
	while (s[k] && s[k] != c)
		k++;
	if (s[k] && j < i && k > i)
		return (1);
	return (0);
}

int			check_error_unexpected(char *s)
{
	int		i;

	i = -1;
	if (s[0] && (s[0] == '|' || s[0] == ';'))
		return (print_error_unexpected(s[0]));
	if (s[0] && s[0] == '<')
		return (print_error_unexpected(s[0]));
	while (s[++i])
	{
		if ((s[i] == '|' || s[i] == ';') && s[i + 1])
		{
			i++;
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 1)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 1)
				return (print_error_nl_expected());
			while (s[i] && s[i] == ' ')
				i++;
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 1)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 1)
				return (print_error_nl_expected());
		}
	}
	return (0);
}

int			check_red(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (i > 0)
	{
		if (line[i - 1] == '<' || line[i - 1] == '>')
			return (print_error_nl_expected());
	}
	return (0);
}
