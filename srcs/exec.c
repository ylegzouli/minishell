#include "../inc/minishell.h"

void		ft_exec_line(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		executor(data, cmd[i]);
		i++;
	}
	//ft_free_split(cmd);
}

void		executor(t_data *data, char *line)
{
	char 	**cmd;
	t_cmd	*new_cmd;
	int		i;
	int		size;

	i = 0;
	size = 0;
	cmd = ft_split_shell(line, '|');
	while (cmd[size])
		size++;
	while (cmd[i] && !(data->exit))
	{
		ft_init_lst(&new_cmd);
		ft_parse(new_cmd, cmd[i], i, size);
		ft_exec_cmd(new_cmd);
		//ft_print_result();
		//ft_lstadd_back_cmd(new_cmd);
		i++;

		printf("cmd= %d\noutput= %d\ninput= %d\nfd_in= %d\narg= [%s]\nresult= [%s]\nret= %d\n-----\n", new_cmd->cmd, new_cmd->output, new_cmd->input, new_cmd->fd_in, new_cmd->arg, new_cmd->result,  g_data->ret);
	}
	//ft_free_split(cmd);
}

void		ft_exec_cmd(t_cmd *cmd)
{
	// il faudrait transformer les cmd en retour int pour les cas d'erreur..
	// ce qu'on peut faire pour gagner de la place par exemple ce serait :
	// if (cmd->cmd == ECHO && echo(cmd->arg, &cmd->result) == 1)
	// 		return (1); ou return(m_error("Erreur sur echo"));

	if (cmd->cmd == ECHO)
			echo(cmd->arg, &cmd->result);
	else if (cmd->cmd == EXPORT)
		export(g_data->lst_env, cmd->arg);
	else if (cmd->cmd == ENV)
		env(g_data->lst_env, &cmd->result);
	else if (cmd->cmd == UNSET)
		unset(g_data->lst_env, cmd->arg);
	else if (cmd->cmd == PWD)
		pwd(g_data);
	else
		printf("Commande fausse, ou pas encore build.\n");
}


