#include "../inc/minishell.h"

int			ft_init_data(t_data *data)
{
	int		i;

	i = -1;
	while (i++ < 1000)
		data->path[i] = '\0';
	find_path(data);
	if (!(data->historic = malloc(sizeof(t_hist))))
		return (ERROR_MALLOC);
	data->historic->next = NULL;
	if (!(data->lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
	if (!(data->lst_env = malloc(sizeof(t_env))))
		return (ERROR_MALLOC);
	data->lst_cmd->next = NULL;
	data->exit = 0;
	data->ret = 0;
	data->pipe = NULL;
	return (SUCCESS);
}

/*
int			ft_init_env()
{
	return (0);
}
*/

int			ft_init_lst(t_cmd **lst_cmd)
{
	if (!(*lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
	(*lst_cmd)->cmd = -1;
	(*lst_cmd)->input = -1;
	(*lst_cmd)->output = -1;
	(*lst_cmd)->fd_in = -1;
	if (!((*lst_cmd)->fd_out = malloc(sizeof(t_list))))
		return (ERROR_MALLOC);
	(*lst_cmd)->fd_out->content = 0;
	(*lst_cmd)->fd_out->next = NULL;
	(*lst_cmd)->result = NULL;
	(*lst_cmd)->next = NULL;
	return (SUCCESS);
}

