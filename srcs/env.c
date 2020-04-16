#include "../inc/minishell.h"

static char		*env_copy(t_env *tmp, char *ret)
{
	int		i;
	
	i = 0;
	while (tmp)
	{
		ft_memcpy(ret + i, tmp->name, ft_strlen(tmp->name));
		i += ft_strlen(tmp->name);
		ret[i] = '=';
		i++;
		ft_memcpy(ret + i, get_env_value(g_data->lst_env, tmp->name), ft_strlen(get_env_value(g_data->lst_env, tmp->name)));
		i += ft_strlen(get_env_value(g_data->lst_env, tmp->name));
		ret[i] = '\n';
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

int				env(t_env *env, char **result)
{
	int		size;
	t_env	*tmp;
	char	*ret;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size += ft_strlen(tmp->name) + 1 + ft_strlen(get_env_value(g_data->lst_env, tmp->name)) + 1;
		tmp = tmp->next;
	}
	size++;
	if (!(ret = malloc(sizeof(char) * size)))
		return (1);
	ret[size] = '\0';	
	tmp = env;
	g_data->ret = 0;
	*result = env_copy(tmp, ret); // il faudrait free *result avant, non?
	write(1, "yolo", 4);
	return (0);	
}

static int	export_env_w(t_env *tmp, char *s)
{
	int		j;
	int		size;

	size = 0;
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

int			command_var_env(t_env *env, t_env *env_w, char *line)
{
	int		i;
	t_env	*tmp;

	tmp = env_w;
	i = 0;
	if (check_variable_env(env, line, check_equal(line)) == 1 ||
		check_variable_env(env_w->next, line, check_equal(line)) == 1) // mystere
	{
		g_data->ret = 0;
		return (0);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	if (export_env_w(tmp, line) == 1)
			return (1);	
	if (i == 0)
		env_w = tmp; // debut du mystere

/*	testeur du mystere ici : env_w est sur un truc chelou au debut	

	printf("real i = %d	\n", i);
	tmp = env_w;
	i = 0;
	while (tmp)
	{
		printf("i = %d, %s = %s\n", i, tmp->name, tmp->value);
		i++;
		tmp=tmp->next;
	}
	*/
	return (0);
}

char		*get_env_value(t_env *env, char *name)
{
	t_env 	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
			tmp = tmp->next;
		else
			return (tmp->value);
	}
	return (0);
}
