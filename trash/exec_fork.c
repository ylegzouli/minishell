#include "../inc/minishell.h"

int			init_fork(t_data *data, char *line)
{
	char    **cmd;
    t_cmd   **new_cmd;
    int     i;
	int		**tube;

	i = 0;
    g_data->i = 0;
    g_data->size = 0;
    g_data->cmd = ft_split_shell(line, '|');
    while (g_data->cmd[g_data->size])
        (g_data->size)++;
   	if (!(*new_cmd = malloc(sizeof(t_cmd *) * g_data->size)))
		return (1);
	if (!(*tube = malloc(sizeof(int *) * g_data->size)))
		return (1);
	while (i < g_data->size)
	{
		if (!(tube[i] = malloc(sizeof(int) * 2)))
			return (1);
		if (pipe(tube[i] == -1))
			return (1);
		i++;
	}

//	if (g_data->cmd[g_data->i] && !(data->exit))
//		creat_fork();
    //ft_free_split(cmd);
}

int			creat_fork(t_cmd **cmd, int **tube)
{
	pid_t	pid;
	char    *tmp;
    char    **arguments;
    char    **environnement;

	ft_init_lst(&cmd[g_data->i]);
    ft_parse(cmd[g_data->i], g_data->cmd[g_data->i], g_data->i, g_data->size);
    if (cmd[g_data->i]->cmd == EXEC 
		&& parsing_file(&environnement, &arguments, &tmp, cmd[g_data->i]))
        return (1);	
	pid = fork();
	if (pid == 0)
	{
		close(tube[g_data->i][0]);
        dup2(tube[g_data->i][1],1);
        close(tube[g_data->i][1]);
        if (execve(tmp, arguments, environnement) == -1)
            return (1);
	}
	else if (pid < 0)
		return (1) ;
	else
	{
		ft_free_split(arguments);
		ft_free_split(environnements);
		(g_data->i)++;
		if (g_data->i < g_data->size)
			creat_fork(cmd, tube);
	}
}

void		creat_pipe()
{

}

/*
void		ft_exec_cmd2(t_cmd *cmd, int *tube[2])
{
    if (cmd->cmd == CD)
        cd(cmd->arg);
    else if (cmd->cmd == EXIT)
        g_data->exit = 1; //ft_exit()   (don't quit if output = PIPE)
    else if (cmd->cmd == EXPORT)
        export(g_data->lst_env, cmd->arg, &cmd->result);
    else if (cmd->cmd == UNSET)
        unset(g_data->lst_env, cmd->arg);
    else if (cmd->cmd == EXEC || cmd->cmd == ECHO || cmd->cmd == ENV || cmd->cmd == PWD)
    {
		if (pipe(tube[g_data->i]))
			return ;
		creat_fork(cmd, tube);
    }
	else
	{
		command_var_env(g_data->lst_env, g_data->lst_env_waiting,
			g_data->cmd_n_found);
		printf("Command fausse\n");
	}
}
*/
