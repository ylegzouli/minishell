/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:55:36 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/04 12:12:22 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			is_quote_dir_pair(char *s, int i, char quote, char dir)
{
	int		j;
	int		count;
	int		signe;

	j = i;
	count = 0;
	if (dir == '<')
		signe = -1;
	else 
		signe = 1;
	while (j >= 0 && s[j])
	{
		if (s[j] == quote)
			count++;
		j = j + signe * 1;
	}
	return (count % 2);
}

int			n_inside_q(char *s, int i)
{
	if (i == ft_strlen(s) - 1)
		return (0);
	if (is_quote_dir_pair(s, i, '"', '<') == 1 && ft_strchr(s + i, '"') != NULL)
		return (1);
	if (is_quote_dir_pair(s, i, 39, '>') == 1 && ft_strchr(s + i, 39) != NULL)
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
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 0)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 0)
				return (print_error_nl_expected());
			while (s[i] && s[i] == ' ')
				i++;
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 0)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 0)
				return (print_error_nl_expected());
		}
		if ((s[i] == '<' || s[i] == '>') && s[i + 1])
		{
			i++;
			if (s[i] && s[i] == ';' && n_inside_q(s, i) == 0)
				return (print_error_unexpected(s[i]));
		}	

	}
	return (0);
}

int			check_red(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (check_err(line) == 1)
		return (print_error_unexpected('>'));
	if (i > 0)
	{
		if (line[i - 1] == '<' || line[i - 1] == '>')
			return (print_error_nl_expected());
	}
	return (0);
}

int			check_err(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
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
