/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:46:24 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/07 11:12:50 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		cd2(char *s, char *save, int i, int j)
{
	if (s[2 * i] == '.' || check_cd_path(s + 3 * i) == 3)
	{
		if (go_there(s + 3 * i) != 0 && ft_strcmp("..", s) != 0)
		{
			print_cd_error(s);
			if (j == 1)
			{
				new_pwd("PWD", get_env_value(g_data->lst_env, "OLDPWD"));
				new_pwd("OLDPWD", save);
				chdir(get_env_value(g_data->lst_env, "PWD"));
				find_path(g_data);
			}
		}
	}
}

static int	from_where(char *s)
{
	if (s[0] == '/')
		return (1);
	else if (s[0] == '~' || s[0] == '\0')
		return (2);
	else
		return (0);
}

static int	go_absolue(char *s)
{
	if (chdir(s) == 0)
	{
		new_pwd("PWD", s);
		return (0);
	}
	g_data->ret = 2;
	return (1);
}

static int	go_in_that_dir(char *s)
{
	char	*path;
	char	*tmp;

	if (s[0] && s[0] == '.' && s[1] == 0 && (g_data->ret = 0) != 1)
		return (0);
	if (!(tmp = ft_strjoin("/", s)))
		return (1);
	if (!(path = ft_strjoin(g_data->path, tmp)))
		return (1);
	if (chdir(path) == 0)
	{
		copy_old_pwd();
		new_pwd("PWD", path);
		find_path(g_data);
		free(path);
		free(tmp);
		g_data->ret = 0;
		return (0);
	}
	chdir(get_env_value(g_data->lst_env, "PWD"));
	free(path);
	free(tmp);
	g_data->ret = 2;
	return (1);
}

int			go_there(char *s)
{
	if (s[0] == '"')
		return (0);
	if (from_where(s) == 1)
	{
		if (go_absolue(s) == 1)
			return (1);
	}
	else if (from_where(s) == 2)
	{
		chdir(get_env_value(g_data->lst_env, "PWD"));
		g_data->ret = 2;
		return (0);
	}
	else if (from_where(s) == 0)
	{
		if (go_in_that_dir(s) == 1)
			return (1);
	}
	g_data->ret = 0;
	return (0);
}
