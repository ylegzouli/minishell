/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:58:59 by acoudouy          #+#    #+#             */
/*   Updated: 2020/05/28 10:59:00 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		free_list_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->name);
		env = tmp->next;
		free(tmp);
		tmp = env;
	}
}

void		free_list_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->name);
		free(tmp->value);
		env = tmp->next;
		free(tmp);
		tmp = env;
	}
}

void		free_split(char **s)
{
	int		i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
