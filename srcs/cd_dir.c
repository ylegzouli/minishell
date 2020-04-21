#include "../inc/minishell.h"

static int	from_where(char *s)
{
	if (s[0] == '/')
		return (1);
	else if (s[0] == '~')
		return (2);
	else
		return (0);
}

static int 	go_absolue(char *s)
{
	if (chdir(s) == 0)
	{
		new_pwd(s);
		return (0);
	}
	g_data->ret = 2;
	return (1);
}

static int	go_in_that_dir(char *s)
{
	char	*path;
	char	*tmp;

	if (!(tmp = ft_strjoin("/", s)))
		return (1);
	if (!(path = ft_strjoin(g_data->path, tmp)))
		return (1);
	if (chdir(path) == 0)
	{
		copy_old_pwd();
		new_pwd(path);
		free(path);
		free(tmp);
		return (0);
	}
	chdir(get_env_value(g_data->lst_env, "PWD"));
	free(path);
	free(tmp);
	g_data->ret = 2;
	return (1);
}

int		go_there(char *s)
{
	if (from_where(s) == 1)
	{
		if (go_absolue(s) == 1)
			return (1);
	}
	else if (from_where(s) == 2)
	{
			write(1, "cd: Not absolute nor relative path\n", 35);
			g_data->ret = 2;
			return (0);
	}
	else if (from_where(s) == 0)
	{
		if (go_in_that_dir(s) == 1)
			return (1);
	}
	g_data->ret = 0;
	return (0);	
}
