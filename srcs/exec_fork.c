/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:55:15 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/29 10:50:12 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			init_fork(char *line)
{
	t_cmd	**new_cmd;
	int		i;
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
		if (!(tube[i] = malloc(sizeof(int) * 2)) || pipe(tube[i]) == -1)
			return (1);
		i++;
	}
	if (g_data->cmd[g_data->i] && !(g_data->exit))
		executor(new_cmd, tube);
	close_tube(tube, *new_cmd);
	free_split(g_data->cmd); //---------> MODIF fais abort echo $var
	free(new_cmd);
	return (0);
}

void		close_tube(int **tube, t_cmd *cmd)
{
	int		i;
	int		status;

	i = 0;
	while (i < g_data->size)
	{
		close(tube[i][0]);
		close(tube[i][1]);
			wait(&status);
			wait(&status);
		free(tube[i]);
		i++;
	}
	free(tube);
	if (cmd->cmd == 9)
		g_data->ret = WEXITSTATUS(status);
	if (cmd->cmd == 8 || cmd->cmd == 9)
		free(g_data->cmd_n_found); // double free non ? 
	dup2(STDOUT_FILENO, STDIN_FILENO);
}

int			executor(t_cmd **cmd, int **tube)
{
	pid_t	pid;
	char	*tmp;
	char	**arguments;
	char	**environnement;

	if (parser(&cmd, &environnement, &arguments, &tmp) == 0
		&& !(g_data->size == 1 && cmd[g_data->i]->cmd != EXEC) && !g_data->exit) //----------- MODIF
	{
		signal(SIGINT, signal_quit);
		signal(SIGQUIT, signal_quit);
		pid = fork();
		if (pid == 0)
		{
			pipe_out(tube[g_data->i]);
			redirect(tube[g_data->i], cmd[g_data->i]);
			if (is_cmd_write(cmd[g_data->i]) == 1)
				ft_exec_cmd(cmd[g_data->i], arguments, environnement, tmp);
			free_data();
			g_data->exit = 1;
		}
		else if (pid < 0)
			return (1);
		if (cmd[g_data->i]->cmd == 9)
			free(tmp);
		dad(tube, cmd, environnement, arguments);

	}
	return (0);
}

void		dad(int **tube, t_cmd **cmd, char **environnement, char **arguments)
{
	int	i;

	i = 0;
	if (cmd[g_data->i]->cmd == 9)
	{	
		free_split(arguments);
		free_split(environnement);
	}
	if (g_data->i < g_data->size - 1 && !(g_data->exit))
	{
		pipe_in(tube[g_data->i], cmd[g_data->i]);
		(g_data->i)++;
		executor(cmd, tube);
	}
}

void		pipe_in(int tube[2], t_cmd *cmd)
{
	if (g_data->i < g_data->size - 1)
	{
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
