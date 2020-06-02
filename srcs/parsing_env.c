/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 11:05:06 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/02 10:08:17 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void			var_env_not_found2(char **ret, char **line,
			int i, int len_var)
{
	while ((*line)[++i] && (*line)[i] != '$')
		(*ret)[i] = (*line)[i];
	len_var--;
	if (i > 0 && (*line)[i - 1] == '"' && (*line)[i + len_var + 1] == '"')
		len_var--;
	while (i < ft_strlen(*line) - 1 - len_var + 1)
	{
		(*ret)[i] = (*line)[i + len_var + 2];
		i++;
	}
	free(*line);
}

static char			*var_env_not_found(t_env *env, char **line)
{
	int		i;
	int		len_var;
	int		size;
	char	*ret;

	i = -1;
	if (check_var_env_return(*line) == 1)
	{
		ret = env_question_found(line);
		return (ret);
	}
	if (check_space_after_dollar(*line) == 1)
	{
		ret = ft_strdup(*line);
		free(*line);
		return (ret);
	}
	len_var = size_var_env_not_found(*line);
	size = ft_strlen(*line) - 1 - len_var;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (0);
	ret[size] = '\0';
	var_env_not_found2(&ret, line, i, len_var);
	return (ret);
}

static char			*var_env_found(t_env *env, char **line, t_env *tmp)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = -1;
	j = -1;
	size = ft_strlen(*line) - 1 - ft_strlen(tmp->name)
		+ ft_strlen(tmp->value) + 1;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (0);
	ret[size] = '\0';
	while ((*line)[++i] && (*line)[i] != '$' && (ft_strncmp(*line + i + 1,
					tmp->name, ft_strlen(tmp->name)) != 0))
		ret[i] = (*line)[i];
	while (tmp->value[++j])
		ret[i + j] = tmp->value[j];
	while (i + j < size)
	{
		ret[i + j] = (*line)[i + ft_strlen(tmp->name) + 1];
		i++;
	}
	free(*line);
	return (ret);
}

char				*parse_env2(char **res, t_env *tmp, t_env *env, int i)
{
	if ((*res)[i + 1] && tmp != 0 &&
		(i + 1 + ft_strlen(tmp->name) >= ft_strlen(*res)
		|| ft_isalpha((*res)[i + 1 + ft_strlen(tmp->name)]) == 0))
		*res = var_env_found(env, res, tmp);
	else
		*res = var_env_not_found(env, res);
	return (*res);
}

char				*parse_env(t_env *env, char *line)
{
	t_env	*tmp;
	int		i;
	char	*res;

	i = -1;
	res = ft_strdup(line);
	while (res[++i])
	{
		tmp = env;
		while (res[i] && res[i] != '$')
			i++;
		if (res[i] && res[i + 1] && (ft_isalpha(res[i + 1]) == 1
				|| res[i + 1] == '?'
				|| res[i + 1] == '_'))
		{
			while (res[i + 1] && tmp && (ft_strncmp(res + i + 1,
				tmp->name, ft_strlen(tmp->name)) != 0))
				tmp = tmp->next;
			res = parse_env2(&res, tmp, env, i);
			i = -1;
		}
	}
	return (res);
}
