#include "../inc/minishell.h"

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

int			create_order_env(t_env *en, char **result)
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
	env(tmp_n_begin, result);
	free_list_export(tmp_n_begin);
	return (0);
}

int			check_arg_export(t_env *env, char *s, char **res)
{
	int		i;

	i = 0;
	if (s[0] == '\0')
	{
		create_order_env(env, res);
		return (2);
	}
	while (s[i] && s[i] != '=')
	{
		if (ft_isalpha(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			export(t_env *env, char *s2, char **res)
{
	t_env 	*tmp;
	int 	size;
	int		j;
	int		i;
	char	**s1;
	char	*s;

	if (s2[0] == '\0')
		return (create_order_env(env, res));
	s1 = ft_split(s2, ' ');
	i = 0;
	while (s1[i])
	{
		size = 0;
		s = s1[i];
		tmp = env;
		if (check_arg_export(env, s, res) == 1)
		{
			g_data->ret = 2;
			write(1, "export: bad variable name\n", 26);
		}
		else if (check_variable_env(env, s, check_char(s, '=')) == 1)
			g_data->ret = 0;
		else if (check_variable_env(g_data->lst_env_waiting, s,
					check_char(s, '=')) == 1)
			switch_to_export(env, g_data->lst_env_waiting, s);
		else if (check_char(s, '=') == 1)
		{
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
		}
		i++;
	}
	//free split 
	return (0);
}
