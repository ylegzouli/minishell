#include "../inc/minishell.h"

int			exec_file(t_cmd *cmd)
{
	pid_t	pid;
	char	*tmp;
	char	**arguments;
	char	**environnement;

	env(g_data->lst_env, &tmp);
	environnement = ft_split(tmp, '\n');
	arguments = ft_split_shell(cmd->arg, ' ');
	//parsing arguments ( ajouter nom du fichier comme 1er arg + attention au " ' et \ ) 
	
	// Ajout d'un check de permissions d'acces au dossier, voir fonction access/chdir
	//check_dir()  --> return un path ?
	pid = fork();
	if (pid == 0)
	{
		if (execve(g_data->cmd_n_found, arguments, environnement) == -1)  //--> ajout arg
			return (1);
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

void		parse_argument();
{
}

char		*check_dir()
{
}
