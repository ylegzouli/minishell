#include "../inc/minishell.h"

void		ft_exec_line(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		init_fork(cmd[i]);
		i++;
	}
	//ft_free_split(cmd);
}

int			is_cmd_write(t_cmd *cmd)
{
	if (cmd->cmd == ECHO || cmd->cmd == ENV || cmd->cmd == PWD)
		return (1);
	if (cmd->cmd == EXEC) // ca prend en compte les not found
		return (1);
	if (cmd->cmd == EXPORT)
	{
		if (cmd->arg[0] == '\0')
			return (1);
	}
	return (0);
}

void		ft_exec_cmd(t_cmd *cmd, char **arg, char **envi, char *path)
{
	// il faudrait transformer les cmd en retour int pour les cas d'erreur..
	// ce qu'on peut faire pour gagner de la place par exemple ce serait :
	// if (cmd->cmd == ECHO && echo(cmd->arg, &cmd->result) == 1)
	// 		return (1); ou return(m_error("Erreur sur echo"));
	if (cmd->cmd == ECHO)
		echo(cmd->arg, &cmd->result);
	else if (cmd->cmd == CD)
		cd(cmd->arg);
	else if (cmd->cmd == EXIT)
		g_data->exit = 1; //ft_exit()   (don't quit if output = PIPE)
	else if (cmd->cmd == EXPORT)
		export(g_data->lst_env, cmd->arg, &cmd->result);
	else if (cmd->cmd == ENV)
		env(g_data->lst_env, &cmd->result, 1);
	else if (cmd->cmd == UNSET)
		unset(g_data->lst_env, cmd->arg);
	else if (cmd->cmd == PWD)
		pwd(g_data, &cmd->result);
	else if (cmd->cmd == EXEC)
		execve(path, arg, envi);
	else if (cmd->cmd == NOTFOUND)
	{
		command_var_env(g_data->lst_env, g_data->lst_env_waiting,
				g_data->cmd_n_found);
		printf("Command fausse\n");
	}
}
