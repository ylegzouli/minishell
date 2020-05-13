#include "../inc/minishell.h" 

void			find_path(t_data *data)
{
	char		tmp[1000];

	ft_bzero(tmp, 1000);
	ft_strdup(getcwd(tmp, 1000));
	ft_strlcpy(data->path, tmp, 1000);
}


void			pwd(t_data *data, char **result, t_cmd *cmd)
{
	find_path(data);
	ft_print(data->path, ft_strlen(data->path), cmd, 1);
//	*result = data->path;
	g_data->ret = 0;
}
