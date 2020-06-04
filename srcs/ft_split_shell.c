/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:09:28 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/04 12:13:04 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		ft_is_sep(char *str, char c2, int i)
{
	if (i > 0 && str[i - 1] == 92)
		return (0);
	if (str[i] == c2 && n_inside_q(str, i) == 0)
		return (1);
	return (0);
}

static char		**ft_strnull(char **liste)
{
	char	**s;
	int		i;

	i = 0;
	if (liste)
	{
		while (liste[i])
		{
			free(liste[i]);
			i++;
		}
		free(liste);
		return (NULL);
	}
	else
	{
		s = malloc(sizeof(char *));
		s[0] = 0;
		return (s);
	}
}

static int		ft_nb(char *str, char charset)
{
	int i;
	int nb_chaine;

	i = 0;
	nb_chaine = 0;
	while (str[i] && ft_is_sep(str, charset, i) == 1)
		i++;
	while (str[i])
	{
		while (str[i] && ft_is_sep(str, charset, i) == 0)
			i++;
		while (str[i] && ft_is_sep(str, charset, i) == 1)
			i++;
		nb_chaine++;
	}
	return (nb_chaine);
}

static char		*ft_create_str(char *str, char charset)
{
	char	*str_ret;
	int		i;

	i = 0;
	while (str[i] && ft_is_sep(str, charset, i) == 0)
		i++;
	if (!(str_ret = malloc((i + 1) * sizeof(char))))
		return (0);
	str_ret[i] = '\0';
	i = 0;
	while (str[i] && ft_is_sep(str, charset, i) == 0)
	{
		str_ret[i] = str[i];
		i++;
	}
	str_ret[i] = '\0';
	return (str_ret);
}

char			**ft_split_shell(char *str, char charset)
{
	int		i;
	int		j;
	char	**liste;

	i = 0;
	j = 0;
	liste = 0;
	if (!(liste = malloc((1 + ft_nb(str, charset)) * sizeof(char *))))
		return (0);
	while (str[i] && ft_is_sep(str, charset, i))
		i++;
	while (str[i])
	{
		if (!(liste[j] = ft_create_str(str + i, charset)))
			return (ft_strnull(liste));
		j++;
		while (str[i] && !ft_is_sep(str, charset, i))
			i++;
		while (str[i] && ft_is_sep(str, charset, i))
			i++;
	}
	liste[j] = 0;
	return (liste);
}
