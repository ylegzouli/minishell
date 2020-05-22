/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:45:32 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/22 12:55:44 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		get_empty_pipe(char **cmd)
{
	char	*tmp;
	char	*line;

	g_data->empty_pipe = 0;
	tmp = ft_strtrim(*cmd, " ");
	if (tmp[ft_strlen(tmp) - 1] == '|')
	{
		g_data->empty_pipe = 1;
		free(*cmd);
		write(1, "> ", 2);
		get_next_line(0, &line);
		*cmd = ft_strjoin(tmp, line);
		free(line);
		if (check_error_unexpected(*cmd))
			exit(1);
		get_empty_pipe(cmd);
	}
	free(tmp);
}

void		parser(t_cmd ***c, char ***envi, char ***arg, char **tmp)
{
	ft_init_lst(&(*c)[g_data->i]);
	ft_parse((*c)[g_data->i], g_data->cmd[g_data->i], g_data->i, g_data->size);
	if ((*c)[g_data->i]->cmd == EXEC)
		parsing_file(envi, arg, tmp, (*c)[g_data->i]);
	if (g_data->size == 1 && (*c)[g_data->i]->cmd != EXEC)
		ft_exec_cmd((*c)[g_data->i], *arg, *envi, *tmp);
}
