/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:43:49 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/07 11:12:15 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int					check_cd_path(char *s)
{
	if (s)
	{
		if (s[0] == '.' && s[1] == '.' &&
			(s[2] == 0 || s[2] == '/'))
			return (1);
		else if (s[0] == '.' && (s[1] == '\0' ||
			s[1] == ' '))
			return (2);
		else if (s[0] != '\0')
			return (3);
		else
			return (4);
	}
	return (-1);
}

int					copy_old_pwd(void)
{
	t_env	*tmp;
	int		size;

	size = 0;
	size = ft_strlen(get_env_value(g_data->lst_env, "PWD"));
	tmp = g_data->lst_env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->name) == 0)
		{
			free(tmp->value);
			if (!(tmp->value = malloc(sizeof(char) * (size + 1))))
				return (1);
			tmp->value[size] = '\0';
			ft_memcpy(tmp->value,
			get_env_value(g_data->lst_env, "PWD"), size);
			return (0);
		}
		else
			tmp = tmp->next;
	}
	g_data->ret = 0;
	return (0);
}

int					new_pwd(char *p, char *s)
{
	t_env		*tmp;

	tmp = g_data->lst_env;
	while (tmp)
	{
		if (ft_strcmp(p, tmp->name) == 0)
		{
			free(tmp->value);
			if (!(tmp->value = malloc(sizeof(char) * (ft_strlen(s) + 1))))
				return (1);
			tmp->value[ft_strlen(s)] = '\0';
			ft_memcpy(tmp->value, s, ft_strlen(s));
			return (0);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

static int			go_up(void)
{
	int		size;

	find_path(g_data);
	size = 0;
	while (g_data->path[size])
		size++;
	size--;
	while (g_data->path[size] && g_data->path[size] != '/')
		size--;
	if (size > 0)
		g_data->path[size] = '\0';
	else
	{
		g_data->path[0] = '/';
		g_data->path[1] = '\0';
	}
	chdir(g_data->path);
	g_data->ret = 0;
	return (0);
}

int					cd(char *s1)
{
	char		**s2;
	char		*s;
	int			i;
	char		*save;
	int			j;

	i = -1;
	j = 0;
	if (s1[0] == 0)
		return (print_cd_error(s1));
	save = ft_strdup(get_env_value(g_data->lst_env, "OLDPWD"));
	s2 = ft_split_shell(s1, ' ');
	delete_quote(&s2[0]);
	s = s2[0];
	while (check_cd_path(s + 3 * ++i) == 1 && (j = 1) != 2)
		go_up();
	if (j == 1 && copy_old_pwd() == 0)
		new_pwd("PWD", g_data->path);
	cd2(s, save, i, j);
	free_split(s2);
	free(save);
	return (0);
}
