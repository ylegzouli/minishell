/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:58:19 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/07 10:15:19 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int				check_quote_export(char **s)
{
	int		i;
	int		q;
	int		k;

	i = 0;
	q = 0;
	k = 0;
	while ((*s)[i] && (*s)[i] != '=')
	{
		if ((*s)[i] == '"')
			q++;
		else if ((*s)[i] != 39)
			k++;
		i++;
	}
	if (q >= 2)
		delete_quote2(s, 0, '"');
	if (k >= 2)
		delete_quote2(s, 0, 39);
	if (q >= 2 || k >= 2)
		return (1);
	return (0);
}

static void		list_sort(t_env **begin_list, int (*cmp)())
{
	t_env	*ptr;
	t_env	*ptr2;
	char	*next;

	ptr = *begin_list;
	while (ptr)
	{
		ptr2 = *begin_list;
		while (ptr2->next && ptr2->next->name)
		{
			if ((*cmp)(ptr2->name, ptr2->next->name) > 0)
			{
				next = ptr2->name;
				ptr2->name = ptr2->next->name;
				ptr2->next->name = next;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

static void		create_order_env2(t_env *tmp_n_begin,
		char **result, t_cmd *cmd)
{
	list_sort(&tmp_n_begin, &ft_strcmp);
	env(tmp_n_begin, result, cmd, 1);
	free_list_export(tmp_n_begin);
}

int				create_order_env(t_env *en, char **result, t_cmd *cmd)
{
	t_env	*tmp_o;
	t_env	*tmp_new;
	t_env	*tmp_n_begin;

	tmp_o = en;
	if (!(tmp_new = malloc(sizeof(t_env))))
		return (1);
	tmp_n_begin = tmp_new;
	while (tmp_o)
	{
		if (!(tmp_new->name = malloc((ft_strlen(tmp_o->name) + 1))))
			return (1);
		ft_memcpy(tmp_new->name, tmp_o->name, ft_strlen(tmp_o->name));
		tmp_new->name[ft_strlen(tmp_o->name)] = '\0';
		tmp_o = tmp_o->next;
		if (tmp_o)
		{
			if (!(tmp_new->next = malloc(sizeof(t_env))))
				return (1);
			tmp_new = tmp_new->next;
		}
	}
	tmp_new->next = 0;
	create_order_env2(tmp_n_begin, result, cmd);
	return (0);
}
