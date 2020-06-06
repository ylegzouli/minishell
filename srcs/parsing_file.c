/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:43 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/06 15:01:39 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*get_path_bin(t_cmd *cmd)
{
	char	*path;
	char	**tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = NULL;
	if (cmd->cmd_n_found[0] && (cmd->cmd_n_found[0] == '/'
		|| cmd->cmd_n_found[0] == '.'))
		path = get_path(cmd->cmd_n_found);
	else
	{
		tmp = ft_split(get_env_value(g_data->lst_env, "PATH"), ':');
		while (tmp[i] && j == 0)
		{
			tmp2 = ft_strjoin(tmp[i], "/");
			path = check_dir(tmp2, &j, cmd);
			free(tmp2);
			i++;
		}
		free_split(tmp);
	}
	return (path);
}

char		*check_dir(char *path, int *j, t_cmd *cmd)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_strcmp(dent->d_name, cmd->cmd_n_found) == 0)
			{
				if (dir)
					closedir(dir);
				*j = 1;
				return (ft_strjoin(path, cmd->cmd_n_found));
			}
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char		*get_name(char *path)
{
	int		i;
	int		size;
	char	*name;

	size = 0;
	i = ft_strlen(path) - 1;
	while (path[i] != '/')
	{
		i--;
		size++;
	}
	name = malloc(sizeof(char) * (size + 2));
	ft_strlcpy(name, &path[i + 1], size + 1);
	name[size] = ' ';
	name[size + 1] = '\0';
	return (name);
}

void		make_quote_great_again(char **s)
{
	int	i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == 1)
			(*s)[i] = '"';
		else if ((*s)[i] == 2)
			(*s)[i] = 39;
		i++;
	}
}

char		**get_arguments(char *path, char *arg)
{
	char	**arguments;
	char	*tmp;
	char	*name;
	int		i;

	i = 0;
	if (!path)
		return (NULL);
	name = get_name(path);
	tmp = ft_strjoin(name, arg);
	arguments = ft_split_shell(tmp, ' ');
	while (arguments[i])
	{
		delete_quote(&(arguments[i]));
		make_quote_great_again(&(arguments[i]));
		i++;
	}
	free(name);
	free(tmp);
	return (arguments);
}
