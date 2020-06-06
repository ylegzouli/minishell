/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:43:49 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/05 09:48:40 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		dupdup(t_cmd *new_cmd, char **tmp, char *cmd)
{
	new_cmd->cmd_n_found = ft_strdup(tmp[0]);
	new_cmd->cmd_temp = ft_strdup(cmd);
	delete_quote(&new_cmd->cmd_n_found);
	new_cmd->cmd = EXEC;
}

char		*parsing_file(char ***envi, char ***arg, char **tmp, t_cmd *cmd)
{
	env(g_data->lst_env, tmp, cmd, 0);
	*envi = ft_split(*tmp, '\n');
	free(*tmp);
	*tmp = NULL;
	if (!(*tmp = get_path_bin(cmd)))
	{
		free_split(*envi);
		cmd->cmd = NOTFOUND;
	}
	*arg = get_arguments(*tmp, cmd->arg);
	return (0);
}
