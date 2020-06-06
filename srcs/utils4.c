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

void		dup()
{
	new_cmd->cmd_n_found = ft_strdup(tmp[0]);
	new_cmd->cmd_temp = ft_strdup(cmd);
	delete_quote(&new_cmd->cmd_n_found);
	new_cmd->cmd = EXEC;
}
