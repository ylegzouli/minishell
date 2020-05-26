/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:43 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/19 15:21:51 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		*parsing_file(char ***envi, char ***arg, char **tmp, t_cmd *cmd)
{
	env(g_data->lst_env, tmp, cmd, 0);
	*envi = ft_split(*tmp, '\n');
	free(*tmp);
	if (!(*tmp = get_path_bin()))
		cmd->cmd = NOTFOUND;
	*arg = get_arguments(*tmp, cmd->arg);
//	free(*tmp);// -----> MODIF fais bug "ls | grep M | wc"
	return (0);
}

char		*get_path_bin(void)
{
	char	*path;
	char	**tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (g_data->cmd_n_found[0] && (g_data->cmd_n_found[0] == '/'
		|| g_data->cmd_n_found[0] == '.'))
		path = get_path(g_data->cmd_n_found);
	else
	{
		tmp = ft_split(get_env_value(g_data->lst_env, "PATH"), ':');
		while (tmp[i] && j == 0)
		{
			tmp2 = ft_strjoin(tmp[i], "/");
			path = check_dir(tmp2, &j);
			free(tmp2);
			i++;
		}
		free_split(tmp);
	}
	return (path);
}

char		*check_dir(char *path, int *j)
{
	DIR				*dir;
	struct dirent	*dent;
//	char			*tmp;

	dir = opendir(path);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_strcmp(dent->d_name, g_data->cmd_n_found) == 0)
			{
				if (dir)
					closedir(dir);
				*j = 1;
			//	tmp = ft_strjoin(path, g_data->cmd_n_found);
			//	free(path);
			//	return (tmp);
				return (ft_strjoin(path, g_data->cmd_n_found));
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

char		**get_arguments(char *path, char *arg)
{
	char	**arguments;
	char	*tmp;
	char	*name;

	if (!path)
		return (NULL);
	name = get_name(path);
	tmp = ft_strjoin(name, arg);
	arguments = ft_split_shell(tmp, ' ');
	free(name);
	free(tmp);
	return (arguments);
}
