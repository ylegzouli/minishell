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
	//arguments = parse_argument();
	arguments = ft_split_shell(cmd->arg, ' ');
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

	if(g_data->cmd_n_found[0] && (g_data->cmd_n_found[0] == '/'
		|| g_data->cmd_n_found[0] == '.'))
	{
		path = get_path(g_data->cmd_n_found);
		//ckecker si le fichier existe ??
	}
	else
	{
		
		path = check_dir();
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
			if (ft_strcmp(dent->d_name, g_data->cmd_n_found))
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

void		parse_argument()
{
	char 	**arg;

	// Ajouter nom du fichier comme 1er arg + attention au \  " '
//	return (arg);
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

//-------------------------------------------------------------------

