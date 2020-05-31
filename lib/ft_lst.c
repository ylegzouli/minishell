/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:20:15 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/22 18:21:32 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			ft_lstadd_front_hist(t_data *data, char *line)
{
	t_hist	*new;

	if (!(new = malloc(sizeof(t_hist))))
		return (ERROR_MALLOC);
	new->line = ft_strdup(line);
	new->next = g_data->historic;
	g_data->historic = new;
	return (SUCCESS);
}

void		ft_lstadd_front_cmd(t_data *data, t_cmd *new)
{
	new->next = data->lst_cmd->next;
	data->lst_cmd = new;
}

void		ft_lstadd_back_cmd(t_cmd *new)
{
	t_cmd	*tmp;

	tmp = g_data->lst_cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
