#include "../inc/minishell.h"

int			export(t_env *env, char *s)
{
	t_env 	*tmp;
	int 	size;
	int		j;

	tmp = env;
	size = 0;
	if (check_variable_env(env, s) == 1)
	{
		g_data->ret = 0;
		return (0);
	}
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

int			check_variable_env(t_env *env, char *s)
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
		else
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
	}
	return (0);
}


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
		ft_memcpy(ret + i, tmp->value, ft_strlen(tmp->value));
		i += ft_strlen(tmp->value);
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
		size += ft_strlen(tmp->name) + 1 + ft_strlen(tmp->value) + 1;
		tmp = tmp->next;
	}
	size++;
	if (!(ret = malloc(sizeof(char) * size)))
		return (1);
	ret[size] = '\0';	
	tmp = env;
	g_data->ret = 0;
	*result = env_copy(tmp, ret); // il faudrait free *result avant, non?
	return (0);	
}
