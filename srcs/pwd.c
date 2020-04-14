#include "../inc/minishell.h" 

void			find_path(t_data *data)
{
	char		tmp[1000];

	ft_bzero(tmp, 1000);
	ft_strdup(getcwd(tmp, 1000));
	ft_strlcpy(data->path, tmp, 1000);
}


void			pwd(t_data *data, char **result)
{
	find_path(data);
	*result = data->path;
	data->ret = 0;
}

/*
**		\o/
**		 |
**		/ \
*/		 
