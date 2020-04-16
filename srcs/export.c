#include "../inc/minishell.h"

static void		print_env_ordered(t_env *sort, t_env *env)
{
	t_env	*tmp;

	tmp = sort;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, get_env_value(env, tmp->name), ft_strlen(get_env_value(env, tmp->name)));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
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
		while (ptr2->next)
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

int			create_order_env(t_env *env)
{
	t_env	*tmp_o;
	t_env	*tmp_new;
	t_env	*tmp_n_begin;

	tmp_o = env;
	if (!(tmp_new = malloc(sizeof(t_env))))
			return (1);
	tmp_n_begin = tmp_new;
	while (tmp_o)
	{
		if(!(tmp_new->name = malloc(sizeof(char) * (ft_strlen(tmp_o->name) + 1))))
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
	list_sort(&tmp_n_begin, &ft_strcmp);
	print_env_ordered(tmp_n_begin, env);
	free_list_export(tmp_n_begin);
	return (0);
}

// ajouter ici si pas d'argument alors lancer le print alpha
int			check_arg_export(t_env *env, char *s)
{
	int		i;

	i = 0;
	if (s[0] == '\0')
	{
		create_order_env(env);
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		if (ft_isalpha(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			export(t_env *env, char *s)
{
	t_env 	*tmp;
	int 	size;
	int		j;

	tmp = env;
	size = 0;
	if (check_arg_export(env, s) == 1)
	{
		g_data->ret = 2;
		write(1, "export: bad variable name\n", 26);
		return (0); // on pourrait mettre au dessus dans la fonction
	}
	if (check_variable_env(env, s, check_equal(s)) == 1 &&
			(g_data->ret = 0))
		return (0);
	if (check_variable_env(g_data->lst_env_waiting->next, s,
				check_equal(s)) == 1)
		return (switch_to_export(env, g_data->lst_env_waiting, s));
	if (check_equal(s) == 0)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_env))))
		return (1);
	tmp = tmp->next;
	while (s[size] && s[size] != '=')
		size++;
	if (!(tmp->name = malloc(sizeof(char) * (size + 1))))
		return (1);
	j = size + 1;
	tmp->name[size] = '\0';
	while (--size >= 0)
		tmp->name[size] = s[size];
	while (s[size + j])
		size++;
	if (!(tmp->value = malloc(sizeof(char) * (size + 1))))
		return (1);
	tmp->value[size] = '\0';
	while (--size >= 0)
		tmp->value[size] = s[j + size];
	tmp->next = 0;
	g_data->ret = 0;
	return (0);
}
