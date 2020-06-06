/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:32:44 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/06 13:12:58 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		ft_exec_line(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	get_empty_pipe(&(data->historic->line));
	if (g_data->empty_pipe == 1)
		return ;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		init_fork(cmd[i]);
		i++;
	}
	free_split(cmd);
}

int			is_cmd_write(t_cmd *cmd)
{
	if (cmd->cmd == ECHO || cmd->cmd == ENV || cmd->cmd == PWD)
		return (1);
	if (cmd->cmd == EXEC)
		return (1);
	if (cmd->cmd == EXPORT)
	{
		if (cmd->arg[0] == '\0')
			return (1);
	}
	if (cmd->cmd == NOTFOUND)
		return (1);
	return (0);
}

void		ft_exec_cmd(t_cmd *cmd, char **arg, char **envi, char *path)
{
	if (cmd->cmd == ECHO)
		echo(cmd->arg, &cmd->result, cmd);
	else if (cmd->cmd == CD)
		cd(cmd->arg);
	else if (cmd->cmd == EXIT)
		ft_exit(cmd);
	else if (cmd->cmd == EXPORT)
		export(g_data->lst_env, cmd->arg, &cmd->result, cmd);
	else if (cmd->cmd == ENV)
		env(g_data->lst_env, &cmd->result, cmd, 1);
	else if (cmd->cmd == UNSET)
		unset(g_data->lst_env, cmd->arg);
	else if (cmd->cmd == PWD)
		pwd(g_data, &cmd->result, cmd);
	else if (cmd->cmd == EXEC)
	{
		if (execve(path, arg, envi) == -1)
			print_cmd_not_found(cmd);
	}
	else if (cmd->cmd == NOTFOUND && command_var_env(g_data->lst_env,
		g_data->lst_env_waiting, cmd->cmd_n_found, cmd) == -1)
		print_cmd_not_found(cmd);
}

void		redirect(int tube[2], t_cmd *cmd)
{
	while (cmd->fd_out && cmd->fd_out->content
		&& *(int *)cmd->fd_out->content != 0)
	{
		dup2(*(int *)cmd->fd_out->content, STDOUT_FILENO);
		close(*(int *)cmd->fd_out->content);
		cmd->fd_out->content = NULL;
		cmd->fd_out = cmd->fd_out->next;
	}
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
}

void		ft_print(char *str, int size, t_cmd *cmd, int i)
{
	t_list	*tmp;

	tmp = cmd->fd_out;
	if (cmd->fd_out->content == NULL)
	{
		write(1, str, size);
		if (i == 1 || i == 2)
			write(1, "\n", 1);
		if (!(i == 2 || i == 3))
			free(str);
		return ;
	}
	while (tmp && tmp->content &&
		*(int *)tmp->content != 0)
	{
		if (tmp->next == NULL)
		{
			write(*(int *)tmp->content, str, size);
			if (i == 1 || i == 2)
				write(*(int *)tmp->content, "\n", 1);
		}
		tmp = tmp->next;
	}
	if (!(i == 2 || i == 3))
		free(str);
}
