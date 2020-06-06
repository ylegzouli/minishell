/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/06 13:16:03 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			ft_parse(t_cmd *new_cmd, char *cmd, int i, int size)
{
	char	*tmp;
	char	*tmp2;

	start_parse(cmd, &tmp);
	if (tmp[0] != 0)
	{
		get_output(new_cmd, &tmp, i, size);
		clean_fdout(&new_cmd->fd_out);
		if (tmp[0] != 0)
		{
			get_cmd(new_cmd, tmp);
			if (new_cmd->cmd == CD)
				direction_cd(&tmp);
			if (get_input(new_cmd, tmp, i, size) == 1)
			{
				free(tmp);
				return (1);
			}
		}
	}
	free(tmp);
	return (0);
}

void		get_cmd(t_cmd *new_cmd, char *cmd)
{
	char **tmp;

	tmp = ft_split(cmd, ' ');
	clean_cmd(&tmp[0]);
	if (ft_strcmp(tmp[0], "exit") == 0)
		new_cmd->cmd = EXIT;
	else if (ft_strcmp(tmp[0], "echo") == 0)
		new_cmd->cmd = ECHO;
	else if (ft_strcmp(tmp[0], "cd") == 0)
		new_cmd->cmd = CD;
	else if (ft_strcmp(tmp[0], "pwd") == 0)
		new_cmd->cmd = PWD;
	else if (ft_strcmp(tmp[0], "export") == 0)
		new_cmd->cmd = EXPORT;
	else if (ft_strcmp(tmp[0], "unset") == 0)
		new_cmd->cmd = UNSET;
	else if (ft_strcmp(tmp[0], "env") == 0)
		new_cmd->cmd = ENV;
	else if (tmp[0])
		dupdup(new_cmd, tmp, cmd);
	free_split(tmp);
}

void		clean_cmd(char **cmd)
{
	char	**tmp;

	if (ft_strchr(*cmd, '<'))
	{
		tmp = ft_split_shell(*cmd, '<');
		free(*cmd);
		*cmd = ft_strdup(tmp[0]);
		free_split(tmp);
	}
	if (ft_strchr(*cmd, '>'))
	{
		tmp = ft_split_shell(*cmd, '>');
		free(*cmd);
		*cmd = ft_strdup(tmp[0]);
		free_split(tmp);
	}
}

int			get_input(t_cmd *new_cmd, char *cmd, int i, int size)
{
	char	**tmp;
	int		j;
	char	*path;

	tmp = ft_split_shell(cmd, '<');
	if (tmp[1] && new_cmd->fd_in == -1)
	{
		clean_input(&path);
		start_input(tmp, &path);
		if ((new_cmd->fd_in = open(path, O_RDONLY)) == -1)
		{
			free_input_error(new_cmd, path, tmp);
			return (1);
		}
		free(path);
	}
	if (i > 0)
		new_cmd->input = PIPE;
	else if (!tmp[1])
		new_cmd->input = ARG;
	get_arg(&new_cmd->arg, tmp[0]);
	if (new_cmd->cmd != EXPORT && new_cmd->cmd != EXEC && new_cmd->cmd != CD)
		delete_quote(&new_cmd->arg);
	free_split(tmp);
	return (0);
}

void		clean_input(char **path)
{
	char	**tmp;

	if (ft_strchr(*path, '>'))
	{
		tmp = ft_split_shell(*path, '>');
		free(*path);
		*path = ft_strdup(ft_strtrim(tmp[0], " "));
		free_split(tmp);
	}
}
