/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:31:59 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/06/01 19:03:51 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		start_parse(char *cmd, char **tmp)
{
	char	*tmp2;

	*tmp = ft_strdup(cmd);
	delete_char(tmp);
	if (check_char(*tmp, '$') == 1)
	{
		tmp2 = parse_env(g_data->lst_env, *tmp);
		free(*tmp);
		*tmp = tmp2;
	}
	tmp2 = ft_strtrim(*tmp, " ");
	free(*tmp);
	*tmp = tmp2;
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
	dup2(STDOUT_FILENO, STDIN_FILENO);
	free_split(g_data->cmd);
}

char		*get_path(char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char 	*path;

	i = 0;
	tmp2 = ft_strdup(str);
	delete_quote(&tmp2);
	if (tmp2[0] == '/')
		return (tmp2);
	else
	{
		path = ft_strjoin(get_env_value(g_data->lst_env, "PWD"), "/");
		tmp = ft_strjoin(path, tmp2);
		free(path);
		free(tmp2);
		return (tmp);
	}
}

int			open_file(char *str, int opt)
{
	int		fd;

	fd = -1;
	if (opt == 1)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0664);
	else if (opt == 2)
		fd = open(str, O_TRUNC | O_RDWR | O_CREAT, 0644);
	return (fd);
}

void		clean_fdout(t_list **fd)
{
	t_list	*tmp;

	if (ft_lstsize(*fd) > 1)
	{
		tmp = *fd;
		*fd = (*fd)->next;
		free(tmp);
	}
}
