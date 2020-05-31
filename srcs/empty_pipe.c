/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:45:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/22 19:45:19 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		get_empty_pipe(char **cmd)
{
	char	*tmp;
	char	*line;

	g_data->empty_pipe = 0;
	if (check_error_unexpected(*cmd))
	{
		g_data->empty_pipe = 1;
		return ;
	}
	tmp = ft_strtrim(*cmd, " ");
	if (tmp[ft_strlen(tmp) - 1] == '|')
	{
		free(*cmd);
		write(1, "> ", 2);
		get_next_line(0, &line);
		*cmd = ft_strjoin(tmp, line);
		free(line);
		get_empty_pipe(cmd);
	}
	free(tmp);
}

int			parser(t_cmd ***c, char ***envi, char ***arg, char **tmp)
{
	ft_init_lst(&(*c)[g_data->i]);
	if (ft_parse((*c)[g_data->i],
		g_data->cmd[g_data->i], g_data->i, g_data->size) == 1)
		return (1);
	if ((*c)[g_data->i]->cmd == EXEC)
		parsing_file(envi, arg, tmp, (*c)[g_data->i]);
	ft_lstadd_back_cmd((*c)[g_data->i]);
	if (g_data->size == 1 && (*c)[g_data->i]->cmd != EXEC)
		ft_exec_cmd((*c)[g_data->i], *arg, *envi, *tmp);
	return (0);
}

void		start_input(char **tmp, char **path)
{
	char	*tmp2;

	tmp2 = ft_strtrim(tmp[1], " ");
	*path = get_path(tmp2);
	free(tmp2);
}
