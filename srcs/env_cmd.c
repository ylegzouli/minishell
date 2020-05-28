/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:55:15 by acoudouy          #+#    #+#             */
/*   Updated: 2020/05/28 10:55:18 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void			switch_to_export2(t_env *env, t_env *tmp, t_env *tmp2)
{
	t_env *tmp_e;

	tmp_e = env;
	while (tmp_e->next)
		tmp_e = tmp_e->next;
	tmp_e->next = tmp;
	tmp2->next = tmp2->next->next;
	tmp->next = 0;
}

int				switch_to_export(t_env *env,
		t_env *env_w, char *s)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		size;

	tmp = env_w;
	size = 0;
	while (s[size] && s[size] != '=')
		size++;
	while (tmp)
	{
		if (ft_strncmp(s, tmp->name, size) != 0)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		else
		{
			switch_to_export2(env, tmp, tmp2);
			break ;
		}
	}
	return (0);
}

static void		unset2(t_env *tmp, t_env *tmp2)
{
	free(tmp->value);
	free(tmp->name);
	tmp2->next = tmp2->next->next;
	free(tmp);
}

void			unset(t_env *env, char *s2)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	**s1;
	int		i;

	tmp = env;
	s1 = ft_split(s2, ' ');
	i = -1;
	while (s1[++i])
	{
		while (tmp)
		{
			if (ft_strcmp(s1[i], tmp->name) != 0)
				tmp2 = tmp;
			else
			{
				unset2(tmp, tmp2);
				break ;
			}
			tmp = tmp->next;
		}
		g_data->ret = 0;
	}
	free_split(s1);
}
