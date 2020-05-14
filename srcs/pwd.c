#include "../inc/minishell.h" 

void			find_path(t_data *data)
{
	char		tmp[1000];

	ft_bzero(tmp, 1000);
//	ft_strdup(getcwd(tmp, 1000));
	getcwd(tmp, 1000);
	ft_strlcpy(data->path, tmp, 1000);
}


void			pwd(t_data *data, char **result, t_cmd *cmd)
{
	find_path(data);
	*result = data->path;
	ft_print(*result, ft_strlen(*result), cmd, 1);
	g_data->ret = 0;
}
