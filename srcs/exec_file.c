#include "../inc/minishell.h"

int			exec_file(t_cmd *cmd)
{
	pid_t	pid;
	int		tube[2];
	char	*tmp;
	char	**arguments;
	char	**environnement;

	env(g_data->lst_env, &tmp);
	environnement = ft_split(tmp, '\n');
	free(tmp);
	tmp = get_path_bin();
	arguments = parse_argument(tmp, cmd->arg);
	if (!tmp)
	{
		// quittez proprement
		return (0);
	}
	if (pipe(tube) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		dup2(tube[1],1);
		if (execve(tmp, arguments, environnement) == -1)
			return (1);
		close(tube[1]);
		kill(pid, SIGKILL); // kill() ou exit() ? voir s'il y'a des leaks avec kill ?
	}
	else if (pid < 0)
		return (1);
	else
		cmd->result = get_result(tube, pid);
	free(tmp);
	//ft_free_split(arguments);
	//ft_free_split(environnement);
	return (0);
}

//-------------------------------------------------------------------

char		*get_path_bin()
{
	char 	*path;
	char	**tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if(g_data->cmd_n_found[0] && (g_data->cmd_n_found[0] == '/'
		|| g_data->cmd_n_found[0] == '.'))
	{
		path = get_path(g_data->cmd_n_found);
		//ckecker si le fichier existe ??
	}
	else
	{
		tmp = ft_split(get_env_value(g_data->lst_env, "PATH"), ':');
		while (tmp[i] && path == NULL)
		{
			tmp2 = ft_strjoin(tmp[i], "/");
			path = check_dir(tmp2);
			free(tmp2);
			i++;
		}
		//ft_free_split(tmp);
	}
	return (path);
}

char		*check_dir(char *path)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_strcmp(dent->d_name, g_data->cmd_n_found) == 0)
			{
				if (dir)
					closedir(dir);
				return (ft_strjoin(path, g_data->cmd_n_found));
			}
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char		**parse_argument(char *path, char *arg)
{
	char 	**arguments;
	char	*tmp;
	char	*name;

	name = get_name(path);
	tmp = ft_strjoin(name, arg);
	arguments = ft_split_shell(tmp, ' ');
	//ft_clean_arg();  --> clean " ' \, 
	free(name);
	free(tmp);
	return (arguments);
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
	ft_strcpy(name, &path[i]);
	name[size - 1] = ' ';
	name[size] = '\0';
	return (name);
}

char		*get_result(int	tube[2], pid_t pid)
{
	char	buf;
	char	*result;

	close(tube[1]);
	wait(&pid);
	result = malloc(sizeof(char));
	result[0] = 0;
	while (read(tube[0], &buf, 1) > 0)
		result = ft_add_char(result, buf);
	return (result);
}
