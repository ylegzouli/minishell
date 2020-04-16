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
			return (4); // go home
	}
}

static int			copy_old_pwd()
{
	t_env 	*tmp;
	int		size;

	size = 0;
	size = ft_strlen(get_env_value(g_data->lst_env, "PWD"));
	tmp = g_data->lst_env;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD", tmp->name, ft_strlen(tmp->name)) == 0)
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
}

int					cd(char *s)
{
	if (copy_old_pwd() == 1)
		return (1);
	printf("oooo");
	if (check_cd_path(s) == 1)
		return (go_up());
//	else if (check_cd_path(s) == 
	return (0);

// il faut maj pwd et old pwd en var env
}
