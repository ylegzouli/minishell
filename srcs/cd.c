#include "../inc/minishell.h"

int					check_cd_path(char *s)
{
	if (s)
	{
		if (s[0] == '.' && s[1] == '.')
			return (1);
		else if (s[0] == '.' && (s[1] == '\0' || s[1] == ' '))
			return (2);
		else if (s[0] != '\0')
			return (3);
		else
			return (4);
	}
}

int			copy_old_pwd()
{
	t_env 	*tmp;
	int		size;

	size = 0;
	size = ft_strlen(get_env_value(g_data->lst_env, "PWD"));
	tmp = g_data->lst_env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->name) == 0)
		{
			free(tmp->value);
			if (!(tmp->value = malloc(sizeof(char) * (size + 1))))
				return (1); 
			tmp->value[size] = '\0';
			ft_memcpy(tmp->value, get_env_value(g_data->lst_env, "PWD"), size);
			return (0);
		}
		else
			tmp = tmp->next;
	}
	g_data->ret = 0;
}

int					new_pwd(char *s)
{
	t_env 	*tmp;

	tmp = g_data->lst_env;
	while (tmp)
	{
		if (ft_strcmp("PWD", tmp->name) == 0)
		{
			free(tmp->value);
			if (!(tmp->value = malloc(sizeof(char) * (ft_strlen(s) + 1))))
				return (1);
			tmp->value[ft_strlen(s)] = '\0';
			ft_memcpy(tmp->value, s, ft_strlen(s));
			return (0);
		}
		else
			tmp = tmp->next;
	}
}

static int			go_up()
{
	int		size;

	size = 0;
	while (g_data->path[size])
		size++;
	size--;
	while (g_data->path[size] && g_data->path[size] != '/')
		size--;
	g_data->path[size] = '\0';
	chdir(g_data->path);
	g_data->ret = 0;
	return (0);
}

int					cd(char *s1)
{
	char		**s2;
	char		*s;
	int			i;

	i = -1;
	s2 = ft_split(s1, ' ');
	s = s2[0];
	while (check_cd_path(s + 3 * ++i) == 1)
		go_up();
	if (s[2 * i] == '\0')
	{
		copy_old_pwd();
		new_pwd(g_data->path);
		free(s2);
		return (0);
	}
	else if (s[2 * i] == '.' || check_cd_path(s + 3 * i) == 3)
	{
		go_there(s + 3 * i);
		free(s2);
		return (0);
	}
	return (0); // je crois que cette ligne ne sert plus
}
