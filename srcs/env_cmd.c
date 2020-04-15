#include "../inc/minishell.h"

int			check_variable_env(t_env *env, char *s, int equal)
{
	t_env		*tmp;
	int			size;
	int			i;

	tmp = env;
	size = 0;
	i = 0;
	while (s[size] && s[size] != '=')
		size++;
	while (tmp)
	{
		if (ft_strncmp(s, tmp->name, size) != 0)
			tmp = tmp->next;
		else if (equal == 1)
		{
			free(tmp->value);
			size++;
			while (s[i + size])
				i++;
			if (!(tmp->value = malloc(sizeof(char) * (i + 1))))
				return (1);
			tmp->value[i] = '\0';
			while (--i >= 0)
				tmp->value[i] = s[i + size];
			return (1);
		}
		else if (equal == 0)
			return (1);
	}
	return (0);
}

int			switch_to_export(t_env *env, t_env *env_w, char *s)
{
	t_env 	*tmp;
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
			t_env *tmp_e; // pour séparer

			tmp_e = env;
			while (tmp_e->next)
				tmp_e = tmp_e->next;
			tmp_e->next = tmp;
			tmp2->next = tmp2->next->next;
			tmp->next = 0;
			break;
		}
	}
	return (0);
}

int 		check_equal(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (i < ft_strlen(s))
		return (1);
	return (0);			
}


int			check_arg_export(char *s)
{
	int		i;

	i = 0;
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
	if (check_arg_export(s) == 1)
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

void			unset(t_env *env, char *s)
{
	t_env 	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(s, tmp->name, ft_strlen(s)) != 0)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		else
		{
			free(tmp->value);
			free(tmp->name);
			tmp2->next = tmp2->next->next;
			free(tmp);
			break;
		}
	}
	g_data->ret = 0;
}

