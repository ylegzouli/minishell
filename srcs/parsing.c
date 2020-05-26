/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/23 01:03:07 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			ft_parse(t_cmd *new_cmd, char *cmd, int i, int size)
{
	if (check_char(cmd, '$') == 1)
		cmd = parse_env(g_data->lst_env, cmd);
	if (cmd[0] != 0)
	{
		get_output(new_cmd, cmd, i, size);
		clean_fdout(&new_cmd->fd_out);
		get_cmd(new_cmd, cmd);
		if (get_input(new_cmd, cmd, i, size) == 1)
			return (1);
	}
	return (0);
}

void		get_cmd(t_cmd *new_cmd, char *cmd)
{
	char **tmp;

	tmp = ft_split(cmd, ' ');
	clean_cmd(&tmp[0]);
	//new_cmd->cmd_temp = ft_strdup(cmd);
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
	{
		g_data->cmd_n_found = ft_strdup(tmp[0]);
		new_cmd->cmd = EXEC;
	}
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

int			new_arg(char *s, char c)
{
	int		i;
	int		j;
	char	*old;

	old = ft_strdup(s);
	i = 0;
	j = 0;
	free(s);
	if (!(s = malloc(ft_strlen(old) - 2)))
		return (-1);
	s[ft_strlen(old) - 2] = 0;
	while (old[i])
	{
		if (old[i] != c)
			s[i - j] = old[i];
		else
			j++;
		i++;
	}
	return (0);
}

int			delete_quote2(char *s, int i, char c)
{
	int pos;

	pos = i;
	while (s[i] && s[i] != c)
		i++;
	i++;
	if (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (s[i])
			return (new_arg(s, c));
	}
	return (0);
}

void		delete_quote(char **arg)
{
	int		i;
	char	*s;

	i = 0;
	s = *arg;
	while (s[i])
	{
		delete_quote2(s, i, 39);
		delete_quote2(s, i, '"');
		i++;
	}
}

int			get_input(t_cmd *new_cmd, char *cmd, int i, int size)
{
	char	**tmp;
	char	*tmp2;
	int		j;
	char	*path;

	tmp = ft_split_shell(cmd, '<');
	if (tmp[1] && new_cmd->fd_in == -1)
	{
		new_cmd->input = REDIRECT;
		path = get_path(ft_strtrim(tmp[1], " "));
		clean_input(&path);
		if ((new_cmd->fd_in = open(path, O_RDONLY)) == -1)
		{	
			write(1, "No sush file or directory\n", 26);
			return (1);
		}
		free(path);
	}
	if (i > 0)
		new_cmd->input = PIPE;
	else if (!tmp[1])
		new_cmd->input = ARG;
	get_arg(&new_cmd->arg, tmp[0]);
	if (new_cmd->cmd != EXPORT)
		delete_quote(&new_cmd->arg);
	free_split(tmp); //--------- MODIF comment free ?
	return (0);
}

void		clean_input(char **path)
{
	char	**tmp;

	if (ft_strchr(*path, '>'))
	{
		tmp = ft_split_shell(*path, '>');
		free(*path);
//		*path = ft_strtrim(tmp[0], " ");
		*path = ft_strdup(ft_strtrim(tmp[0], " "));
		free_split(tmp);
	}
}

void		get_arg(char **arg, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split_shell(str, '>');
	while (tmp[0][i] == ' ')
		i++;
	while (tmp[0][i] && tmp[0][i] != ' ')
		i++;
	while (tmp[0][i] == ' ')
		i++;
//	*arg = ft_strdup(ft_strtrim(&tmp[0][i], " "));
	*arg = ft_strtrim(&tmp[0][i], " ");
	free_split(tmp);
}
