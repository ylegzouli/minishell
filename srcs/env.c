/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:49:11 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/01 19:54:57 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char		*env_copy(t_env *tmp, char *ret)
{
	int		i;

	i = 0;
	while (tmp)
	{
		ft_memcpy(ret + i, tmp->name, ft_strlen(tmp->name));
		i += ft_strlen(tmp->name);
		ret[i] = '=';
		i++;
		ft_memcpy(ret + i, get_env_value(g_data->lst_env, tmp->name),
		ft_strlen(get_env_value(g_data->lst_env, tmp->name)));
		i += ft_strlen(get_env_value(g_data->lst_env, tmp->name));
		ret[i] = '\n';
		i++;
		tmp = tmp->next;
	}
	ret[i] = '\0';
	return (ret);
}

int				env(t_env *env, char **result,
			t_cmd *cmd, int print)
{
	int		size;
	t_env	*tmp;
	char	*ret;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size += ft_strlen(tmp->name) + 1 +
		ft_strlen(get_env_value(g_data->lst_env, tmp->name)) + 1;
		tmp = tmp->next;
	}
	size++;
	if (!(ret = malloc(sizeof(char) * size)))
		return (1);
	ret[size - 1] = '\0';
	tmp = env;
	g_data->ret = 0;
	*result = env_copy(tmp, ret);
	if (print == 1)
		ft_print(*result, ft_strlen(*result), cmd, 3);
	if (cmd->cmd == 5)
		free(ret);
	return (0);
}

int				export_env_w(t_env *tmp, char *s)
{
	int		j;
	int		size;

	size = 0;
	if (!(tmp->next = malloc(sizeof(t_env))))
		return (1);
	tmp = tmp->next;
	while (s[size] && s[size] != '=')
		size++;
	if (!(tmp->name = malloc(sizeof(char) * (size + 1))))
		return (1);
	j = size + 1;
	tmp->name[size] = '\0';
	while (--size >= 0)
		tmp->name[size] = s[size];
	while (s[size + j])
		size++;
	if (s[size + j - 1] == '"' || s[size + j - 1] == 39)
		return (export_quoted(tmp, s, size, j));
	else
		return (export_no_quote(tmp, s, size, j));
	return (0);
}

char			*get_cmd_n_found(t_cmd *cmd)
{
	char	**tmp;
	char	*nl;

	tmp = ft_split_shell(cmd->cmd_temp, ' ');
	nl = ft_strdup(tmp[0]);
	free_split(tmp);
	return (nl);
}

int				check_arg_not_found(char *s)
{
	int	i;

	i = 0;
	if (s && s[0] == '=')
		return (1);
	while (s[i] && s[i] != '=')
	{
		if (ft_isalpha(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
