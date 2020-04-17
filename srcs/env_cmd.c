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
		if (ft_strcmp(s, tmp->name) != 0)
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
		else if (equal == 0 && ft_strlen(tmp->name) > 0)
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

void			unset(t_env *env, char *s2)
{
	t_env 	*tmp;
	t_env	*tmp2;
	char	**s1;
	int		i;
	char	*s;

	tmp = env;
	s1 = ft_split(s2, ' ');
	i = 0;
	while (s1[i])
	{
		s = s1[i];
		while (tmp)
		{
			if (ft_strcmp(s, tmp->name) != 0)
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
		i++;
	}
	/// faudra free le split
}

