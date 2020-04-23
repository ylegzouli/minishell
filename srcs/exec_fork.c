#include "../inc/minishell.h"

int			init_fork(char *line)
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
   	if (!(new_cmd = malloc(sizeof(t_cmd *) * g_data->size)))
		return (1);
	if (!(tube = malloc(sizeof(int *) * g_data->size)))
		return (1);
	while (i < g_data->size)
	{
		if (!(tube[i] = malloc(sizeof(int) * 2)))
			return (1);
		if (pipe(tube[i]) == -1)
			return (1);
		i++;
	}
	if (g_data->cmd[g_data->i] && !(g_data->exit))
		executor(new_cmd, tube);
	i = 0;
	while (i < g_data->size)
	{
		close(tube[i][0]);
		close(tube[i][1]);
		wait(NULL);
		wait(NULL);
		i++;
	}
//	dup2(1, 0);
	dup2(STDOUT_FILENO, STDIN_FILENO);
	//ft_free_split(cmd);
	return (0);
}

int			executor(t_cmd **cmd, int **tube)
{
	pid_t	pid;
	char    *tmp;
    char    **arguments;
    char    **environnement;
	int		i;

	i = 0;
	ft_init_lst(&cmd[g_data->i]);
    ft_parse(cmd[g_data->i], g_data->cmd[g_data->i], g_data->i, g_data->size);
    if (cmd[g_data->i]->cmd == EXEC) 
		parsing_file(&environnement, &arguments, &tmp, cmd[g_data->i]);
	if (g_data->size == 1 && cmd[g_data->i]->cmd != EXEC)
		ft_exec_cmd(cmd[g_data->i], arguments, environnement, tmp);
	else
	{
		g_data->thread = 1;
		signal(SIGINT, signal_quit);
		signal(SIGQUIT, signal_quit);
		pid = fork();
		if (pid == 0)
		{
			pipe_out(tube[g_data->i]);
			if (is_cmd_write(cmd[g_data->i]) == 1)
				ft_exec_cmd(cmd[g_data->i], arguments, environnement, tmp);
			g_data->exit = 1;
		}
		else if (pid < 0)
			return (1) ;
		else if (g_data->i < g_data->size - 1 && !(g_data->exit))
		{
			//ft_free_split(arguments);
			//ft_free_split(environnements);
			pipe_in(tube[g_data->i], cmd[g_data->i]);
			(g_data->i)++;
			executor(cmd, tube);
		}
		else
		{	
			//ft_free_split(arguments);   !!!!! free impossible ? !!!!!
			//ft_free_split(environnements);
		}
	}
	g_data->thread = 0;
	return (0);
}

void		pipe_in(int tube[2], t_cmd *cmd)
{
	if (g_data->i < g_data->size - 1)
	{
//		redirect(tube);
		if (cmd->cmd != EXEC)
			wait(NULL);
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
	}
}

void		pipe_out(int tube[2])
{
	if (g_data->i < g_data->size - 1)
	{	
		close(tube[0]);
		dup2(tube[1], STDOUT_FILENO);
	}
}
