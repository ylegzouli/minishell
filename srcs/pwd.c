#include "../inc/minishell.h" 

void			find_path(t_data *data)
{
	char		tmp[1000];

	ft_bzero(tmp, 1000);
	ft_strdup(getcwd(tmp, 1000));
	ft_strlcpy(data->path, tmp, 1000);
}


void			pwd(t_data *data)
{
	find_path(data);
	write(1, data->path, ft_strlen(data->path));
	write(1, "\n", 3);
	data->ret = 0;
}

/*
**		\o/
**		 |
**		/ \
*/		 
