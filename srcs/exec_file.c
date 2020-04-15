#include "../inc/minishell.h"

int			exec_file(t_cmd *cmd)
{
	pid_t	pid;
	char	*tmp;
	char	**arguments;
	char	**environnement;

	env(g_data->lst_env, &tmp);
	environnement = ft_split(tmp, '\n');
	free(tmp);
	//tmp = get_path_bin();
	//arguments = parse_argument();
	arguments = ft_split_shell(cmd->arg, ' ');
	if (!tmp)
	{
		// quittez proprement
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(g_data->cmd_n_found, arguments, environnement) == -1)  //--> ajout arg
			return (1);
		// Penser a quitter le fork si erreur de lancement (exit())
	}
	else if (pid < 0)
		return (1);
	else
		wait(&pid);
	free(tmp);
	//ft_free_split(arguments);
	//ft_free_split(environnement);
	return (0);
}

char		*get_path_bin()
{
	char 	*path;

	//if(PATH ABSOLU)
		//path = g_data->cmd_n_found;
	//else
		//path = check_dir();
	return (path);
}

char		*check_dir()
{
	// Tester tous les chemins contenu dans $PATH
	// pour verifier si le binaire existe
	return (path);
}

void		parse_argument()
{
	char 	**arg;

	// Ajouter nom du fichier comme 1er arg + attention au \  " '
	return (arg);
}


