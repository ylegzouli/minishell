/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:09:28 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/21 11:11:16 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		ft_is_sep(const char *str, char c2, char *quote, int i)
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

static int		ft_nb(const char *str, char charset, char *quote)
{
	int i;
	int nb_chaine;

	i = 0;
	nb_chaine = 0;
	while (str[i] && ft_is_sep(str, charset, quote, i))
		i++;
	while (str[i])
	{
		while (str[i] && !ft_is_sep(str, charset, quote, i))
			i++;
		while (str[i] && ft_is_sep(str, charset, quote, i))
			i++;
		nb_chaine++;
	}
	return (nb_chaine);
}

static char		*ft_create_str(const char *str, char charset, char *quote)
{
	char	*str_ret;
	int		i;

	i = 0;
	while (str[i] && !ft_is_sep(str, charset, quote, i))
		i++;
	if (!(str_ret = malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (str[i] && !ft_is_sep(str, charset, quote, i))
	{
		str_ret[i] = str[i];
		i++;
	}
	str_ret[i] = '\0';
	return (str_ret);
}

char			**ft_split_shell(char const *str, char charset)
{
	int		i;
	int		j;
	char	quote;
	char	**liste;

	i = 0;
	j = 0;
	quote = 0;
	liste = 0;
	if (str == 0)
		return (ft_strnull(liste));
	if (!(liste = malloc((1 + ft_nb(str, charset, &quote)) * sizeof(char *))))
		return (0);
	while (str[i] && quote == 0 && ft_is_sep(str, charset, &quote, i))
		i++;
	while (str[i])
	{
		if (!(liste[j] = ft_create_str(str + i, charset, &quote)))
			return (ft_strnull(liste));
		j++;
		while (str[i] && !ft_is_sep(str, charset, &quote, i))
			i++;
		while (str[i] && ft_is_sep(str, charset, &quote, i))
			i++;
	}
	liste[j] = 0;
	return (liste);
}
